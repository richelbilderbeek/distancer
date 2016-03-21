#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <utility>

class parameters
{
public:
  parameters(
    const int max_genetic_distance,
    const double mutation_rate,
    const int n_generations,
    const std::size_t n_loci,
    const int population_size,
    const int rng_seed,
    const int sampling_interval
  );

  ///Number of loci per individual
  std::size_t get_n_loci() const noexcept { return m_n_loci; }

  ///RNG seed
  int get_rng_seed() const noexcept { return m_rng_seed; }

  ///Number of generations the simulation will run
  int get_n_generations() const noexcept { return m_n_generations; }

  ///The constant population size
  int get_population_size() const noexcept { return m_population_size; }

  ///The maximum number of alleles two individuals may differ
  ///and still produce viable offspring
  int get_max_genetic_distance() const noexcept { return m_max_genetic_distance; }

  ///Chance to have 1 locus flipped in a genome
  double get_mutation_rate() const noexcept { return m_mutation_rate; }

  ///After how many generations is the population sampled for species abundances
  int get_sampling_interval() const noexcept { return m_sampling_interval; }


private:

  ///The maximum number of alleles two individuals may differ
  ///and still produce viable offspring
  int m_max_genetic_distance;

  ///Chance to have 1 locus flipped in a genome
  double m_mutation_rate;

  ///Number of generations the simulation will run
  int m_n_generations;

  ///Number of loci per individual
  std::size_t m_n_loci;

  ///The constant population size
  int m_population_size;

  ///RNG seed
  int m_rng_seed;

  ///After how many generations is the population sampled for species abundances
  int m_sampling_interval;

};

#endif // PARAMETERS_H
