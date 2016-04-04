#ifndef DISTANCER_RESULTS_GRAPH_H
#define DISTANCER_RESULTS_GRAPH_H

#include <boost/graph/adjacency_list.hpp>
#include "distancer_results_vertex.h"

using results_graph = boost::adjacency_list<
  boost::vecS,
  boost::vecS,
  boost::undirectedS,
  results_vertex
>;

#endif // DISTANCER_RESULTS_GRAPH_H
