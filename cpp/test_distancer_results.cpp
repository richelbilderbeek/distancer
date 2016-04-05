#include "distancer_results.h"
#include <boost/test/unit_test.hpp>
#include <boost/graph/adjacency_list.hpp>
#include "distancer_population_factory.h"

// From a population, create a single node phylogeny:
//
// +----+
// | 00 | <- genotype
// | 02 | <- frequency
// +----+
BOOST_AUTO_TEST_CASE(test_results_create_single_node_phylogeny)
{
  results r;
  const int max_genetic_distance{1};
  const pin my_pin("");
  const sil my_sil(2, 0b00);
  std::vector<individual> p{
    individual(my_pin, my_sil)
  };

  r.add_measurement(0, p, max_genetic_distance);

  const auto g = r.get_sil_frequency_phylogeny();
  BOOST_CHECK_EQUAL(boost::num_vertices(g), 1);
  BOOST_CHECK_EQUAL(get_vertex_frequency(*vertices(g).first, g), 1);
  BOOST_CHECK_EQUAL(get_vertex_sil(*vertices(g).first, g), my_sil);
  BOOST_CHECK_EQUAL(get_vertex_pin(*vertices(g).first, g), my_pin);
}


