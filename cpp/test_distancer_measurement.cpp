#include "distancer_measurement.h"
#include <cassert>
#include <boost/test/unit_test.hpp>

#include "distancer_individual.h"
#include "distancer_population_factory.h"



BOOST_AUTO_TEST_CASE(test_measurement_population_no_individuals)
{

  const int max_genetic_distance{1};
  const auto population = population_factory().create_population_no_individuals();
  const measurement m(population, max_genetic_distance);
  BOOST_CHECK_EQUAL(m.get_n_species(), 0);
  BOOST_CHECK_EQUAL(m.get_n_possible_species(), 0);
}

BOOST_AUTO_TEST_CASE(test_measurement_population_one_individual)
{
  const int max_genetic_distance{1};
  const auto population = population_factory().create_population_one_individual();
  const measurement m(population, max_genetic_distance);
  BOOST_CHECK_EQUAL(m.get_n_species(), 1);
  BOOST_CHECK_EQUAL(m.get_n_possible_species(), 1);
}

BOOST_AUTO_TEST_CASE(test_measurement_population_two_individuals_one_species)
{
  const int max_genetic_distance{1};
  const auto population = population_factory().create_population_two_individuals_one_species();
  const measurement m(population, max_genetic_distance);
  BOOST_CHECK_EQUAL(m.get_n_species(), 1);
  BOOST_CHECK_EQUAL(m.get_n_possible_species(), 1);
}

BOOST_AUTO_TEST_CASE(test_measurement_population_two_individuals_two_species)
{
  const int max_genetic_distance{1};
  const auto population = population_factory().create_population_two_individuals_two_species();
  const measurement m(population, max_genetic_distance);
  BOOST_CHECK_EQUAL(m.get_n_species(), 2);
  BOOST_CHECK_EQUAL(m.get_n_possible_species(), 2);
}
