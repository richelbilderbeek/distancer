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

std::ostream& operator<<(std::ostream& os, const results& r) noexcept
{
  os << r.get_sil_frequency_phylogeny();
  //?Newline is required by R's read.table function
  return os;
}
