#include "distancer.h"
#include <exception>
#include <iostream>
#include <fstream>
#include "helper.h"

int main() {
  #ifndef NDEBUG
  std::ofstream f("exe_debug.txt");
  #else
  std::ofstream f("exe_release.txt");
  #endif
  try
  {
    const int max_genetic_distance{1};
    const double mutation_rate{0.1}; //Chance to have 1 locus flipped in a genome
    const int n_generations{1000000000};
    const int n_loci{16};
    const int population_size{8};
    const int rng_seed{42};
    const parameters p(
      max_genetic_distance,
      mutation_rate,
      n_generations,
      n_loci,
      population_size,
      rng_seed
    );
    do_simulation(p);
    std::fstream f;
    const std::string filename{"results.csv"};
    if (!is_regular_file(filename))
    {
      std::cerr << "Error: file '" << filename
        << "' not found" <<'\n';
      return 1;
    }
    const auto v = file_to_vector(filename);
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
