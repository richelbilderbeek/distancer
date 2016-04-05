#include "distancer_simulation.h"
#include <boost/test/unit_test.hpp>

#include "distancer_simulation.h"
#include <exception>
#include <iostream>
#include <fstream>
#include "distancer_helper.h"
#include "is_regular_file.h"
#include "convert_dot_to_svg.h"
#include "convert_svg_to_png.h"

BOOST_AUTO_TEST_CASE(test_do_simulation_run_example_sim)
{
  //Copy the main function here
  try
  {
    const int max_genetic_distance{1};
    const int n_generations{3000};
    const int n_pin_loci{5};
    const int n_sil_loci{4};
    const double pin_mutation_rate{0.1}; //Chance to have 1 locus flipped in a genome
    const int population_size{8};
    const std::string results_filename{"results.dot"};
    const int rng_seed{30};
    const int sampling_interval{150};
    const double sil_mutation_rate{0.1}; //Chance to have 1 locus flipped in a genome
    const parameters p(
      max_genetic_distance,
      n_generations,
      n_pin_loci,
      n_sil_loci,
      pin_mutation_rate,
      population_size,
      results_filename,
      rng_seed,
      sampling_interval,
      sil_mutation_rate
    );
    do_simulation(p);
    BOOST_CHECK(is_regular_file(results_filename));
    convert_dot_to_svg(results_filename, "results.svg");
    convert_svg_to_png("results.svg", "results.png");
  }
  catch (std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    BOOST_CHECK(!"Should not get here");
  }
  catch (...)
  {
    std::cerr << "Error: Unknown\n";
    BOOST_CHECK(!"Should not get here");
  }
}
