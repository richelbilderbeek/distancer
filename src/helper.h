#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

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

///Create a tally of value occurrances
///For example {0,1,1,2,2,2} would result in {1,2,3}
///The sum of the tally will be equal to the length of the input vector
std::vector<int> create_tally(const std::vector<int>& v) noexcept;

///FileToVector reads a file and converts it to a std::vector<std::string>
///From http://www.richelbilderbeek.nl/CppFileToVector.htm
std::vector<std::string> file_to_vector(const std::string& filename);

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

#endif // HELPER_H
