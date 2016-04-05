#include "distancer_results.h"
#include <iostream>
#include <sstream>
#include "add_bundled_vertex.h"
#include "distancer_sil.h"
#include "distancer_helper.h"
#include "add_bundled_edge.h"

results::results()
  : m_sil_frequency_phylogeny{},
    m_vds_prev{}
{

}

void results::add_measurement(
  const int t ,
  const population& any_population,
  const int max_genetic_distance
) noexcept
{
  if (t < 0)
  {
    std::stringstream msg;
    msg << __func__ << ": generation 't' cannot be "
      << "negative, value supplied is " << t
    ;
    throw std::invalid_argument(msg.str());
  }
  //Tally SILs
  const std::map<sil,int> m = tally_sils(any_population);

  std::vector<sil_frequency_vertex_descriptor> vds;

  //Add vertices, collect vertex descriptors
  for (const auto p: m)
  {
    std::map<sil,int> sil_frequencies;
    sil_frequencies.insert(std::make_pair(p.first, p.second));

    const auto vd = add_bundled_vertex(
      sil_frequency_vertex(
        sil_frequencies,
        t
      ),
      m_sil_frequency_phylogeny
    );
    vds.push_back(vd);
  }

  //Connect vertices of same species in this timestep
  const int n_vds{static_cast<int>(vds.size())};
  for (int i=0; i!=n_vds; ++i)
  {
    for (int j=i+1; j!=n_vds; ++j)
    {
      assert(i >= 0);
      assert(i < n_vds);
      assert(j >= 0);
      assert(j < n_vds);
      const auto v_a = m_sil_frequency_phylogeny[ vds[i] ];
      const auto v_b = m_sil_frequency_phylogeny[ vds[j] ];
      const auto silfs_a = v_a.get_sil_frequencies();
      const auto silfs_b = v_b.get_sil_frequencies();
      assert(silfs_a.size() == 1);
      assert(silfs_b.size() == 1);
      const auto sil_a = (*silfs_a.begin()).first;
      const auto sil_b = (*silfs_b.begin()).first;
      if (count_different_bits(sil_a, sil_b) <= max_genetic_distance)
      {
        add_bundled_edge(
          vds[i],
          vds[j],
          sil_frequency_edge(0),
          m_sil_frequency_phylogeny
        );
      }
    }
  }

  //Connect vertices with the same and close SILs
  const int n_vds_prev{static_cast<int>(m_vds_prev.size())};
  for (int i=0; i!=n_vds; ++i)
  {
    for (int j=0; j!=n_vds_prev; ++j)
    {
      assert(i >= 0);
      assert(i < n_vds);
      const auto vd_now = vds[i];
      assert(j >= 0);
      assert(j < n_vds_prev);
      const auto vd_prev = m_vds_prev[j];
      const auto v_a = m_sil_frequency_phylogeny[ vd_now ];
      const auto v_b = m_sil_frequency_phylogeny[ vd_prev ];
      const auto silfs_a = v_a.get_sil_frequencies();
      const auto silfs_b = v_b.get_sil_frequencies();
      assert(silfs_a.size() == 1);
      assert(silfs_b.size() == 1);
      const auto sil_a = (*silfs_a.begin()).first;
      const auto sil_b = (*silfs_b.begin()).first;
      assert(sil_a.size() == sil_b.size());
      if (count_different_bits(sil_a, sil_b) <= max_genetic_distance)
      {
        add_bundled_edge(
          vd_now,
          vd_prev,
          sil_frequency_edge(1),
          m_sil_frequency_phylogeny
        );
      }
    }
  }

  //Keep the newest vds
  m_vds_prev = vds;
}

void results::summarize_genotypes()
{
  if (boost::num_vertices(m_sil_frequency_phylogeny) == 0) return;

  const auto vds = vertices(m_sil_frequency_phylogeny);
  for (auto vd = vds.first; vd != vds.second; ++vd)
  {
    const auto t = m_sil_frequency_phylogeny[*vd].get_time();
    //For all vertices, find the neighbors
    const auto neighbors = boost::adjacent_vertices(*vd, m_sil_frequency_phylogeny);
    for (auto neighbor = neighbors.first; neighbor != neighbors.second; ++neighbor)
    {
      //If a neighbor is of the same generation, move all connections and genotypes to it
      const auto t_neighbor = m_sil_frequency_phylogeny[*neighbor].get_time();
      if (t != t_neighbor) continue; //Nope
      //Move genotypes
      try
      {
        assert(*vd != *neighbor);
        move_sil_frequencies(m_sil_frequency_phylogeny[*vd], m_sil_frequency_phylogeny[*neighbor]);
      }
      catch (std::invalid_argument& e)
      {
        std::cerr
          << "Focal vertex: " << m_sil_frequency_phylogeny[*vd] << '\n'
          << "Neighbor vertex: " << m_sil_frequency_phylogeny[*neighbor] << '\n'
        ;
        throw e;
      }
      assert(m_sil_frequency_phylogeny[*vd].get_sil_frequencies().empty());
      assert(m_sil_frequency_phylogeny[*neighbor].get_sil_frequencies().size() >= 2);
      //Move edges
      for (auto other_neighbor = neighbors.first; other_neighbor != neighbors.second; ++other_neighbor)
      {
        //No self loops
        if (neighbor == other_neighbor) continue;
        //No adding new edges
        if (edge(*neighbor, *other_neighbor, m_sil_frequency_phylogeny).second) continue;
        //Add it. Because all edges between species are already present, new edges
        //will be between generations
        add_bundled_edge(
          *neighbor,
          *other_neighbor,
          sil_frequency_edge(1),
          m_sil_frequency_phylogeny
        );
      }
      //Delete this vertex its edges
      boost::clear_vertex(*vd, m_sil_frequency_phylogeny);
      break;
    }
  }

  //Delete all genotypes without frequencies (nor connections)
  for (int i = boost::num_vertices(m_sil_frequency_phylogeny) - 1; i!=-1; --i)
  {
    const auto vd = vds.first + i;
    if (degree(*vd, m_sil_frequency_phylogeny) == 0) {
      boost::remove_vertex(*vd, m_sil_frequency_phylogeny);
    }
  }
}

std::ostream& operator<<(std::ostream& os, const results& r) noexcept
{
  os << r.get_sil_frequency_phylogeny();
  //?Newline is required by R's read.table function
  return os;
}
