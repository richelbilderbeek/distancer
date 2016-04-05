#include "distancer_results.h"
#include <iostream>
#include <sstream>
#include "add_bundled_vertex.h"
#include "distancer_sil.h"
#include "save_bundled_vertices_graph_to_dot.h"
#include "distancer_helper.h"

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
    const auto vd = add_bundled_vertex(
      sil_frequency_vertex(
        p.second,
        p.first,
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
      const auto a = m_sil_frequency_phylogeny[ vds[i] ].get_sil();
      const auto b = m_sil_frequency_phylogeny[ vds[j] ].get_sil();
      if (count_different_bits(a, b) <= max_genetic_distance)
      {
        boost::add_edge(vds[i], vds[j], m_sil_frequency_phylogeny);
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
      const auto a = m_sil_frequency_phylogeny[ vd_now ].get_sil();
      const auto b = m_sil_frequency_phylogeny[ vd_prev ].get_sil();
      assert(a.size() == b.size());
      if (count_different_bits(a, b) <= max_genetic_distance)
      {
        boost::add_edge(vd_now, vd_prev, m_sil_frequency_phylogeny);
      }
    }
  }

  //Keep the newest vds
  m_vds_prev = vds;
}

std::ostream& operator<<(std::ostream& os, const results& r) noexcept
{
  const auto g = r.get_sil_frequency_phylogeny();
  boost::write_graphviz(os, g,
    sil_frequency_vertex_writer<sil_frequency_phylogeny>(g)
  );
  //?Newline is required by R's read.table function
  return os;
}
