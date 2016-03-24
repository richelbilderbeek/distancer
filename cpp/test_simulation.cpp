#include "simulation.h"
#include <fstream>
#include "helper.h"
#include <boost/test/unit_test.hpp>

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

BOOST_AUTO_TEST_CASE(test_do_simulation_zero_generations_zero_rows)
{
  const int max_genetic_distance{1};
  const int n_generations{0};
  const std::size_t n_pin{1};
  const std::size_t n_sil{1};
  const double pin_mutation_rate{0.1};
  const int population_size{1};
  const std::string results_filename{"tmp.txt"};
  const int rng_seed{42};
  const int sampling_interval{1};
  const double sil_mutation_rate{0.1};
  const parameters p(
    max_genetic_distance,
    n_generations,
    n_pin,
    n_sil,
    pin_mutation_rate,
    population_size,
    results_filename,
    rng_seed,
    sampling_interval,
    sil_mutation_rate
  );
  do_simulation(p);
  BOOST_CHECK(is_regular_file(results_filename));
  const auto v = file_to_vector(results_filename);
  std::remove(results_filename.c_str());

  // first line is header, last line must be empty for R
  BOOST_CHECK(v.size() == n_generations + 2);
}

BOOST_AUTO_TEST_CASE(test_do_simulation_one_generations_one_rows)
{
  const int max_genetic_distance{1};
  const int n_generations{1};
  const std::size_t n_pin{1};
  const std::size_t n_sil{1};
  const double pin_mutation_rate{0.1};
  const int population_size{1};
  const int rng_seed{42};
  const std::string results_filename{"tmp.txt"};
  const int sampling_interval{1};
  const double sil_mutation_rate{0.1};
  const parameters p(
    max_genetic_distance,
    n_generations,
    n_pin,
    n_sil,
    pin_mutation_rate,
    population_size,
    results_filename,
    rng_seed,
    sampling_interval,
    sil_mutation_rate
  );
  do_simulation(p);
  BOOST_CHECK(is_regular_file(results_filename));
  const auto v = file_to_vector(results_filename);
  std::remove(results_filename.c_str());

  // first line is header, last line must be empty for R
  BOOST_CHECK(v.size() == n_generations + 2);
}

BOOST_AUTO_TEST_CASE(test_do_simulation_ten_generations_ten_rows)
{
  const int max_genetic_distance{1};
  const int n_generations{10};
  const std::size_t n_pin{1};
  const std::size_t n_sil{1};
  const double pin_mutation_rate{0.1};
  const int population_size{1};
  const std::string results_filename{"tmp.txt"};
  const int rng_seed{42};
  const int sampling_interval{1};
  const double sil_mutation_rate{0.1};
  const parameters p(
    max_genetic_distance,
    n_generations,
    n_pin,
    n_sil,
    pin_mutation_rate,
    population_size,
    results_filename,
    rng_seed,
    sampling_interval,
    sil_mutation_rate
  );
  do_simulation(p);
  BOOST_CHECK(is_regular_file(results_filename));
  const auto v = file_to_vector(results_filename);
  std::remove(results_filename.c_str());

  // first line is header, last line must be empty for R
  BOOST_CHECK(v.size() == n_generations + 2);
}

#pragma GCC diagnostic pop
