#include "individual.h"

#include <boost/graph/adjacency_list.hpp>
#include "helper.h"

individual::individual(const size_t n_loci, const size_t sil_value)
  : m_sil{sil_t(n_loci, sil_value)}
{

}

individual::individual(const sil_t& sil)
  : m_sil{sil}
{

}


std::vector<int> count_abundances(
  std::vector<individual> p,
  const int max_genetic_distance
) noexcept
{
  if (p.empty()) return {};

  const int sz{static_cast<int>(p.size())};
  if (sz == 1) return { static_cast<int>(p.size()) };

  boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> g(sz);

  for (int i=0; i!=sz; ++i)
  {
    for (int j=i+1; j!=sz; ++j)
    {
      const int genetic_distance{get_genetic_distance(p[i],p[j])};
      if (genetic_distance <= max_genetic_distance)
      {
        const auto vip = vertices(g);
        auto from_iter = vip.first + i;
        auto to_iter = vip.first + j;
        boost::add_edge(*from_iter, *to_iter, g);
      }
    }
  }
  const auto ids = get_connected_components_ids(g);
  return create_tally(ids);
}

int count_species(std::vector<individual> p, const int max_genetic_distance) noexcept
{
  //const bool debug{false};
  if (p.empty()) return 0;

  //Ditch the duplicates to speed up the calculation
  std::sort(
    std::begin(p),std::end(p), [](const individual& lhs, const individual& rhs)
    {
      return lhs.get_sil().to_ulong() < rhs.get_sil().to_ulong();
    }
  );
  typename std::vector<individual>::iterator new_end = std::unique(std::begin(p),std::end(p));
  p.erase(new_end,std::end(p));

  const int sz{static_cast<int>(p.size())};
  if (sz == 1) return 1;

  boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> g(sz);

  for (int i=0; i!=sz; ++i)
  {
    for (int j=i+1; j!=sz; ++j)
    {
      const int genetic_distance{get_genetic_distance(p[i],p[j])};
      if (genetic_distance <= max_genetic_distance)
      {
        const auto vip = vertices(g);
        auto from_iter = vip.first + i;
        auto to_iter = vip.first + j;
        boost::add_edge(*from_iter, *to_iter, g);
      }
    }
  }
  return count_connected_components(g);
}

int get_genetic_distance(
  const individual& a,
  const individual& b
) noexcept
{
  const individual::sil_t d = a.get_sil() ^ b.get_sil();
  return d.count();
}

bool operator==(const individual& lhs, const individual& rhs) noexcept
{
  return lhs.get_sil() == rhs.get_sil();
}

bool operator!=(const individual& lhs, const individual& rhs) noexcept
{
  return !(lhs == rhs);
}
