#include "distancer_sil_frequency_phylogeny.h"
#include <iostream>
#include <boost/graph/graphviz.hpp>
#include "distancer_sil_frequency_vertex_writer.h"

std::ostream& to_stream(
  std::ostream& os,
  const sil_frequency_phylogeny& g,
  const int max_genetic_distance
) noexcept
{
  boost::write_graphviz(os, g,
    sil_frequency_vertex_writer<sil_frequency_phylogeny>(g, max_genetic_distance),
    sil_frequency_edge_writer<sil_frequency_phylogeny>(g)
  );
  return os;
}
