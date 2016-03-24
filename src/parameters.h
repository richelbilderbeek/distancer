#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <string>
#include <utility>

class parameters
{
public:
  parameters(
    const int max_genetic_distance,
    const double mutation_rate,
    const int n_generations,
    const std::size_t n_pin_loci,
    const std::size_t n_sil_loci,
    const int population_size,
    const std::string& results_filename,
    const int rng_seed,
    const int sampling_interval
  );

  ///Number of PIN per individual (PIN: Phylogeny Inferring Nucleotides)
  std::size_t get_n_pin_loci() const noexcept { return m_n_pin_loci; }

  ///Number of SIL per individual (SIL: Species Identity Loci)S
  std::size_t get_n_sil_loci() const noexcept { return m_n_sil_loci; }

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

  ///The filename of the file the results will be written to
  const std::string& get_results_filename() const noexcept { return m_results_filename; }

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

  ///Number of PINs per individual (PIN: Phylogeny Inferring Nucleotides)
  std::size_t m_n_pin_loci;

  ///Number of SILs per individual (SIL: Species Identity Loci)
  std::size_t m_n_sil_loci;

  ///The constant population size
  int m_population_size;

  ///The filename of the file the results will be written to
  std::string m_results_filename;

  ///RNG seed
  int m_rng_seed;

  ///After how many generations is the population sampled for species abundances
  int m_sampling_interval;

};

#endif // PARAMETERS_H
