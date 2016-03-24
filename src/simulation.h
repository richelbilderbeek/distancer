#ifndef DISTANCER_H
#define DISTANCER_H

#include "parameters.h"

///Return something
void do_simulation(const parameters& p);

//' The function that does a simulation.
//' @param max_genetic_distance the maximum number of different loci that two individuals can still produce viable offspring with
//' @param mutation_rate DNA mutation rate
//' @param n_generations number of generations
//' @param n_pin number of Phylogeny Inferring Nucleotides
//' @param n_sil number of Species Identity Loci
//' @param population_size population size
//' @param results_filename the name of the file the results will be written to
//' @param rng_seed random number generator seed
//' @param sampling_interval after how many generations is the population sampled for species abundances
//' @return nothing. A file with name 'results_filename' will be created
//' @export
// [[Rcpp::export]]
void do_simulation_cpp(
  const int max_genetic_distance,
  const double mutation_rate,
  const int n_generations,
  const int n_pin, //Use int over std::size_t for r
  const int n_sil, //Use int over std::size_t for r
  const int population_size,
  const std::string& results_filename,
  const int rng_seed,
  const int sampling_interval
);

#endif // DISTANCER_H

