#include "distancer_sil_frequency_phylogeny.h"
#include <boost/test/unit_test.hpp>
#include "add_bundled_vertex.h"
#include "distancer_sil_frequency_vertex.h"
#include "distancer_individual.h"

BOOST_AUTO_TEST_CASE(test_results_graph)
{
  sil_frequency_phylogeny g;
  BOOST_CHECK_EQUAL(boost::num_vertices(g), 0);

  const int frequency{42};
  const sil my_sil(2, 0b00);
  const int time{123};
  add_bundled_vertex(
    sil_frequency_vertex(
      frequency,
      my_sil,
      time
    )
    , g
  );

  BOOST_CHECK_EQUAL(boost::num_vertices(g), 1);
  BOOST_CHECK_EQUAL(get_vertex_frequency(*vertices(g).first, g), frequency);
  BOOST_CHECK_EQUAL(get_vertex_sil(*vertices(g).first, g), my_sil);
  BOOST_CHECK_EQUAL(get_vertex_time(*vertices(g).first, g), time);
}



