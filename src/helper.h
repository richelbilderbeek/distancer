#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/dynamic_bitset.hpp>
#include "dna.h"

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

///Counts the number of bits that are different
int count_different_bits(
  const boost::dynamic_bitset<>& a,
  const boost::dynamic_bitset<>& b
) noexcept;

///Create a bitset that has its bits inherited from its
///ancestors p and q.
///The 'inherit_from_p' determines per bit if that locus is inherited
///from ancestor p.
boost::dynamic_bitset<> create_offspring(
  const boost::dynamic_bitset<>& p,
  const boost::dynamic_bitset<>& q,
  const boost::dynamic_bitset<>& inherit_from_p
);

///Create a sequence that has its nucleotides inherited from its
///ancestors p and q.
///The 'inherit_from_p' determines per site if that nucleotide is inherited
///from ancestor p.
dna create_offspring(
  const dna& p,
  const dna& q,
  const boost::dynamic_bitset<>& inherit_from_p
);

///Create a tally of value occurrances
///For example {0,1,1,2,2,2} would result in {1,2,3}
///The sum of the tally will be equal to the length of the input vector
std::vector<int> create_tally(const std::vector<int>& v) noexcept;


///FileToVector reads a file and converts it to a std::vector<std::string>
///From http://www.richelbilderbeek.nl/CppFileToVector.htm
std::vector<std::string> file_to_vector(const std::string& filename);

///Get the indices of the value that have a 1 bit
/// get_bits(0) == { }
/// get_bits(1) == { 0 }
/// get_bits(2) == { 1 }
/// get_bits(3) == { 0, 1 }
/// get_bits(4) == { 2 }
/// get_bits(5) == { 0, 2 }
/// get_bits(6) == { 1, 2 }
/// get_bits(7) == { 0, 1, 2 }
std::vector<int> get_bits(const int value);

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

///Determines if a filename is a regular file
///From http://www.richelbilderbeek.nl/CppIsRegularFile.htm
bool is_regular_file(const std::string& filename) noexcept;

///Copied from the BoostGraphTutorial
template <typename graph>
void remove_nth_vertex(
  const size_t i,
  graph& g
)
{
  static_assert(!std::is_const<graph>::value,
    "graph cannot be const"
  );
  if (i >= boost::num_vertices(g))
  {
    std::stringstream msg;
    msg << __func__ << ": "
      << "cannot delete nth (n == " << i
      << ") vertex for graph with "
      << boost::num_vertices(g) << " vertices"
    ;
    throw std::invalid_argument(msg.str());
  }
  const auto vds = vertices(g);
  const auto vd = vds.first + i;
  boost::clear_vertex(*vd, g);
  boost::remove_vertex(*vd, g);
}

#endif // HELPER_H
