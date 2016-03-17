#include <fstream>
#include "distancer.h"

#define BOOST_TEST_DYN_LINK // Defines a main function
#define BOOST_TEST_MODULE distancer
#include <boost/test/unit_test.hpp>

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

BOOST_AUTO_TEST_SUITE(distancer_functions)

BOOST_AUTO_TEST_CASE(test_do_simulation)
{
  const int max_genetic_distance{1};
  const double mutation_rate{0.1};
  const int n_generations{1};
  const std::size_t n_loci{1};
  const int population_size{1};
  const int rng_seed{42};
  const parameters p(
    max_genetic_distance,
    mutation_rate,
    n_generations,
    n_loci,
    population_size,
    rng_seed
  );
  const auto v = do_simulation(p);
  BOOST_CHECK(v.size() == 1);

}


BOOST_AUTO_TEST_SUITE_END()

//Your code
#pragma GCC diagnostic pop
