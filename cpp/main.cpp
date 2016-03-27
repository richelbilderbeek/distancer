#include "simulation.h"
#include <exception>
#include <iostream>
#include <fstream>
#include "helper.h"

int main() {
  try
  {
    const int max_genetic_distance{1};
    const int n_generations{3000};
    const int n_pin_loci{5};
    const int n_sil_loci{4};
    const double pin_mutation_rate{0.1}; //Chance to have 1 locus flipped in a genome
    const int population_size{8};
    const std::string results_filename{"results.csv"};
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
    if (!is_regular_file(results_filename))
    {
      std::cerr << "Error: file '" << results_filename
        << "' not found" <<'\n';
      return 1;
    }
    const auto v = file_to_vector(results_filename);
    std::copy(
      std::begin(v),
      std::end(v),
      std::ostream_iterator<std::string>(std::cout, "\n")
    );
  }
  catch (std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Error: Unknown\n";
    return 1;
  }
}
