#ifndef DISTANCER_H
#define DISTANCER_H

#include <boost/dynamic_bitset.hpp>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include "parameters.h"

///Counts the number of components in a graph
///For example: A-B C-D would a graph of two edges, four vertices and two connected component
template <typename graph>
int count_connected_components(
  const graph& g
) noexcept
{
  std::vector<int> c(boost::num_vertices(g));
  const int n = boost::connected_components(g,
    boost::make_iterator_property_map(
      std::begin(c),
      get(boost::vertex_index, g)
    )
  );
  return n;
}

///Count the number of ring species, where two individuals must have at most 'max_genetic_distance'
///genetic difference to be called the same species
int count_species(std::vector<boost::dynamic_bitset<>> p, const int max_genetic_distance) noexcept;

///Return something
void do_simulation(const parameters& p);

//Do not define this here: R will get confused
//void do_simulation_cpp(...)


///Counts the number of loci that are different
int get_genetic_distance(
  const boost::dynamic_bitset<>& a,
  const boost::dynamic_bitset<>& b
) noexcept;

#endif // DISTANCER_H

