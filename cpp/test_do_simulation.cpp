#include <fstream>
#include "distancer.h"
#include "helper.h"

//#define BOOST_TEST_MODULE distancer
#include <boost/test/unit_test.hpp>

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

BOOST_AUTO_TEST_SUITE(distancer_functions)

BOOST_AUTO_TEST_CASE(test_do_simulation_zero_generations_zero_rows)
{
  const int max_genetic_distance{1};
  const double mutation_rate{0.1};
  const int n_generations{0};
  const std::size_t n_loci{1};
  const int population_size{1};
  const int rng_seed{42};
  const int sampling_interval{1};
  const parameters p(
    max_genetic_distance,
    mutation_rate,
    n_generations,
    n_loci,
    population_size,
    rng_seed,
    sampling_interval
  );
  do_simulation(p);
  const std::string filename{"results.csv"};
  BOOST_CHECK(is_regular_file(filename));
  const auto v = file_to_vector(filename);

  // first line is header, last line must be empty for R
  BOOST_CHECK(v.size() == n_generations + 2);
}

BOOST_AUTO_TEST_CASE(test_do_simulation_one_generations_one_rows)
{
  const int max_genetic_distance{1};
  const double mutation_rate{0.1};
  const int n_generations{1};
  const std::size_t n_loci{1};
  const int population_size{1};
  const int rng_seed{42};
  const int sampling_interval{1};
  const parameters p(
    max_genetic_distance,
    mutation_rate,
    n_generations,
    n_loci,
    population_size,
    rng_seed,
    sampling_interval
  );
  do_simulation(p);
  const std::string filename{"results.csv"};
  BOOST_CHECK(is_regular_file(filename));
  const auto v = file_to_vector(filename);

  // first line is header, last line must be empty for R
  BOOST_CHECK(v.size() == n_generations + 2);
}

BOOST_AUTO_TEST_CASE(test_do_simulation_ten_generations_ten_rows)
{
  const int max_genetic_distance{1};
  const double mutation_rate{0.1};
  const int n_generations{10};
  const std::size_t n_loci{1};
  const int population_size{1};
  const int rng_seed{42};
  const int sampling_interval{1};
  const parameters p(
    max_genetic_distance,
    mutation_rate,
    n_generations,
    n_loci,
    population_size,
    rng_seed,
    sampling_interval
  );
  do_simulation(p);
  const std::string filename{"results.csv"};
  BOOST_CHECK(is_regular_file(filename));
  const auto v = file_to_vector(filename);

  // first line is header, last line must be empty for R
  BOOST_CHECK(v.size() == n_generations + 2);
}


BOOST_AUTO_TEST_SUITE_END()

//Your code
#pragma GCC diagnostic pop
