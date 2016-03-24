#include "parameters.h"
#include <fstream>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "helper.h"

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

BOOST_AUTO_TEST_CASE(test_parameters)
{
  const int max_genetic_distance{1};
  const double mutation_rate{0.1};
  const int n_generations{10};
  const std::size_t n_pin_loci{2};
  const std::size_t n_sil_loci{2};
  const int population_size{10};
  const std::string results_filename{"tmp.txt"};
  const int rng_seed{42};
  const int sampling_interval{1};

  BOOST_CHECK_NO_THROW(
    parameters(
      max_genetic_distance,
      mutation_rate,
      n_generations,
      n_pin_loci,
      n_sil_loci,
      population_size,
      results_filename,
      rng_seed,
      sampling_interval
    )
  );

  BOOST_CHECK_THROW(
    parameters(
      -1, //max_genetic_distance,
      mutation_rate,
      n_generations,
      n_pin_loci,
      n_sil_loci,
      population_size,
      results_filename,
      rng_seed,
      sampling_interval
    ),
    std::invalid_argument
  );

  BOOST_CHECK_THROW(
    parameters(
      max_genetic_distance,
      -0.1, //mutation_rate,
      n_generations,
      n_pin_loci,
      n_sil_loci,
      population_size,
      results_filename,
      rng_seed,
      sampling_interval
    ),
    std::invalid_argument
  );
  BOOST_CHECK_THROW(
    parameters(
      max_genetic_distance,
      1.1, //mutation_rate,
      n_generations,
      n_pin_loci,
      n_sil_loci,
      population_size,
      results_filename,
      rng_seed,
      sampling_interval
    ),
    std::invalid_argument
  );
  BOOST_CHECK_THROW(
    parameters(
      max_genetic_distance,
      mutation_rate,
      -1, //n_generations,
      n_pin_loci,
      n_sil_loci,
      population_size,
      results_filename,
      rng_seed,
      sampling_interval
    ),
    std::invalid_argument
  );
  BOOST_CHECK_NO_THROW(
    parameters(
      max_genetic_distance,
      mutation_rate,
      n_generations,
      -1, //n_loci, gets implicitly converted to unsigned integer
      -1, //same here
      population_size,
      results_filename,
      rng_seed,
      sampling_interval
    )
  );
  BOOST_CHECK_THROW(
    parameters(
      max_genetic_distance,
      mutation_rate,
      n_generations,
      n_pin_loci,
      n_sil_loci,
      -1, //population_size,
      results_filename,
      rng_seed,
      sampling_interval
    ),
    std::invalid_argument
  );
  BOOST_CHECK_THROW(
    parameters(
      max_genetic_distance,
      mutation_rate,
      n_generations,
      n_pin_loci,
      n_sil_loci,
      population_size,
      "", //results_filename,
      rng_seed,
      sampling_interval
    ),
    std::invalid_argument
  );
  BOOST_CHECK_THROW(
    parameters(
      max_genetic_distance,
      mutation_rate,
      n_generations,
      n_pin_loci,
      n_sil_loci,
      population_size,
      results_filename,
      rng_seed,
      -1 //sampling_interval
    ),
    std::invalid_argument
  );
  //Cannot sample less often than the number of generations
  BOOST_CHECK_THROW(
    parameters(
      max_genetic_distance,
      mutation_rate,
      10, //n_generations,
      n_pin_loci,
      n_sil_loci,
      population_size,
      results_filename,
      rng_seed,
      1000 //sampling_interval
    ),
    std::invalid_argument
  );
}

#pragma GCC diagnostic pop



