#include "distancer.h"
#include <exception>
#include <iostream>
#include <fstream>

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
