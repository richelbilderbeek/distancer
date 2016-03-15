#ifndef DISTANCER_H
#define DISTANCER_H

#include <bitset>
#include <boost/dynamic_bitset.hpp>
#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

///Counts the number of components in a graph
///For example: A-B C-D would a graph of two edges, four vertices and two connected component
template <typename graph>
int count_connected_components(
  const graph& g
) noexcept
{
  const bool debug{false};
  std::vector<int> c(boost::num_vertices(g));
  const int n = boost::connected_components(g,
    boost::make_iterator_property_map(
      std::begin(c),
      get(boost::vertex_index, g)
    )
  );

  if (debug) {
    std::copy(std::begin(c),std::end(c),std::ostream_iterator<int>(std::cout, ", "));
    std::cout << '\n';
  }
  return n;
}

///Count the number of ring species, where two individuals must have at most 'max_genetic_distance'
///genetic difference to be called the same species
int count_species(std::vector<boost::dynamic_bitset<>> p, const int max_genetic_distance) noexcept;

///The function that does a simulation
void do_simulation(const size_t n_loci);

///Counts the number of loci that are different
template <size_t n_loci>
int get_genetic_distance(
  const std::bitset<n_loci>& a,
  const std::bitset<n_loci>& b
) noexcept
{
  const std::bitset<n_loci> d = a ^ b;
  return d.count();
}

///Counts the number of loci that are different
int get_genetic_distance(
  const boost::dynamic_bitset<>& a,
  const boost::dynamic_bitset<>& b
) noexcept;


///Count the number of ring species, where two individuals must have at most 'max_genetic_distance'
///genetic difference to be called the same species
template <size_t n_loci>
int count_species(std::vector<std::bitset<n_loci>> p, const int max_genetic_distance) noexcept
{
  const bool debug{false};
  if (p.empty()) return 0;
  std::sort(std::begin(p),std::end(p), [](const std::bitset<n_loci>& lhs, const std::bitset<n_loci>& rhs) { return lhs.to_ulong() < rhs.to_ulong(); } );
  typename std::vector<std::bitset<n_loci>>::iterator new_end = std::unique(std::begin(p),std::end(p));
  p.erase(new_end,std::end(p));

  const int sz{static_cast<int>(p.size())};
  if (sz == 1) return 1;

  boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> g(sz);
  assert(sz == static_cast<int>(boost::num_vertices(g)));

  for (int i=0; i!=sz; ++i)
  {
    if (debug) { std::cout << "i (" << i << ") has genome " << p[i] << '\n'; }
    for (int j=i+1; j!=sz; ++j)
    {
      assert(j < sz);
      const int genetic_distance{get_genetic_distance(p[i],p[j])};
      if (debug) { std::cout << "j (" << j << ") has genome " << p[j] << " and genetic distance " << genetic_distance << '\n'; }
      if (genetic_distance <= max_genetic_distance)
      {
        if (debug) { std::cout << "MATCH\n"; }
        const auto vip = vertices(g);
        auto from_iter = vip.first + i;
        auto to_iter = vip.first + j;
        boost::add_edge(*from_iter, *to_iter, g);
      }
      else
      {
        if (debug) { std::cout << "No match\n"; }
      }
    }
  }
  return count_connected_components(g);
}

#endif // DISTANCER_H

