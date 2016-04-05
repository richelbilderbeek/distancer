#include "distancer_sil_frequency_vertex.h"
#include <boost/test/unit_test.hpp>
#include <boost/graph/adjacency_list.hpp>
#include "distancer_population_factory.h"

BOOST_AUTO_TEST_CASE(test_results_vertex_default_construction)
{
  sil_frequency_vertex v;
  BOOST_CHECK(v.get_sil_frequencies().empty());
  BOOST_CHECK_EQUAL(v.get_time(), 0);
}
