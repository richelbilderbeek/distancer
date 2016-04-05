#include "distancer_results_vertex.h"
#include <boost/test/unit_test.hpp>
#include <boost/graph/adjacency_list.hpp>
#include "distancer_population_factory.h"

BOOST_AUTO_TEST_CASE(test_results_vertex_default_construction)
{
  results_vertex v;
  BOOST_CHECK_EQUAL(v.get_sil(), sil());
  BOOST_CHECK_EQUAL(v.get_pin(), pin());
  BOOST_CHECK_EQUAL(v.get_frequency(), 0);
}
