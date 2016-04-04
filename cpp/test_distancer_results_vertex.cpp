#include "distancer_results_vertex.h"
#include <boost/test/unit_test.hpp>
#include <boost/graph/adjacency_list.hpp>
#include "distancer_population_factory.h"

BOOST_AUTO_TEST_CASE(test_results_vertex)
{
  results_vertex v;
  /*
  //v.m_sil
  const int max_genetic_distance{1};
  const individual ::pin_t pin("");
  const individual::sil_t sil(2, 0b00);
  std::vector<individual> p{
    individual(pin, sil)
  };

  r.add_measurement(0, p, max_genetic_distance);
  */
  /*
  const auto g = r.get_genotype_frequency_phylogeny();
  BOOST_CHECK_EQUAL(boost::num_vertices(g), 1);
  BOOST_CHECK_EQUAL(get_vertex_sil(*vertices(g).first, g), sil);
  BOOST_CHECK_EQUAL(get_vertex_pin(*vertices(g).first, g), pin);
  BOOST_CHECK_EQUAL(get_vertex_frequency(*vertices(g).first, g), 1);
  */
  BOOST_CHECK_EQUAL(1,2); //TODO
}



