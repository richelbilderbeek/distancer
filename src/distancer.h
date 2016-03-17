#ifndef DISTANCER_H
#define DISTANCER_H

#include <boost/dynamic_bitset.hpp>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include "parameters.h"

///Count the number of ring species, where two individuals must have at most 'max_genetic_distance'
///genetic difference to be called the same species
std::vector<int> count_abundances(
  std::vector<boost::dynamic_bitset<>> p,
  const int max_genetic_distance
) noexcept;

///Get the ID of each node in a graph, which differs per connected component
///For example: A-B C-D would a graph of two edges, four vertices and two connected component
///The IDs returned would be {0,0,1,1}
template <typename graph>
std::vector<int> get_connected_components_ids(
  const graph& g
) noexcept
{
  std::vector<int> c(boost::num_vertices(g));
  boost::connected_components(g,
    boost::make_iterator_property_map(
      std::begin(c),
      get(boost::vertex_index, g)
    )
  );
  return c;
}

///Counts the number of components in a graph
///For example: A-B C-D would a graph of two edges, four vertices and two connected components
///The value returned would be 2
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

///Create a tally of value occurrances
///For example {0,1,1,2,2,2} would result in {1,2,3}
///The sum of the tally will be equal to the length of the input vector
std::vector<int> create_tally(const std::vector<int>& v) noexcept;

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

