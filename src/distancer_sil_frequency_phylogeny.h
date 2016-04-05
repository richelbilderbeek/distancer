#ifndef DISTANCER_RESULTS_GRAPH_H
#define DISTANCER_RESULTS_GRAPH_H

#include <boost/graph/adjacency_list.hpp>
#include "distancer_sil_frequency_vertex.h"

using sil_frequency_phylogeny = boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::undirectedS,
  sil_frequency_vertex
>;

using sil_frequency_vertex_descriptor
  = boost::graph_traits<sil_frequency_phylogeny>::vertex_descriptor;

#endif // DISTANCER_RESULTS_GRAPH_H
