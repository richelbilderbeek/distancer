#include "distancer_results_graph.h"
#include <boost/test/unit_test.hpp>
#include "add_bundled_vertex.h"
#include "distancer_results_vertex.h"

BOOST_AUTO_TEST_CASE(test_results_graph)
{
  results_graph g;
  BOOST_CHECK_EQUAL(boost::num_vertices(g), 0);

  const individual::pin_t pin("");
  const individual::sil_t sil(2, 0b00);
  add_bundled_vertex(results_vertex(), g);

  BOOST_CHECK_EQUAL(boost::num_vertices(g), 1);
  BOOST_CHECK_EQUAL(get_vertex_sil(*vertices(g).first, g), sil);
  BOOST_CHECK_EQUAL(get_vertex_pin(*vertices(g).first, g), pin);
  BOOST_CHECK_EQUAL(get_vertex_frequency(*vertices(g).first, g), 1);
}



