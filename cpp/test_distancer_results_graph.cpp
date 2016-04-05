#include "distancer_results_graph.h"
#include <boost/test/unit_test.hpp>
#include "add_bundled_vertex.h"
#include "distancer_results_vertex.h"
#include "distancer_individual.h"

BOOST_AUTO_TEST_CASE(test_results_graph)
{
  results_graph g;
  BOOST_CHECK_EQUAL(boost::num_vertices(g), 0);

  const int frequency{42};
  const pin my_pin("ACGT");
  const sil my_sil(2, 0b00);
  add_bundled_vertex(
    results_vertex(
      frequency,
      my_pin,
      my_sil
    )
    , g
  );

  BOOST_CHECK_EQUAL(boost::num_vertices(g), 1);
  BOOST_CHECK_EQUAL(get_vertex_frequency(*vertices(g).first, g), frequency);
  BOOST_CHECK_EQUAL(get_vertex_pin(*vertices(g).first, g), my_pin);
  BOOST_CHECK_EQUAL(get_vertex_sil(*vertices(g).first, g), my_sil);
}



