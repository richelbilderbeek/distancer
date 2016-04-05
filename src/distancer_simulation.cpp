#include "distancer_simulation.h"

#include <algorithm>
#include <fstream>
#include <random>
#include <boost/graph/isomorphism.hpp>
#include "distancer_individual.h"
#include "distancer_results.h"
//#include "distancer_helper.h"


void do_simulation(const parameters& my_parameters)
{
  results my_results;
  const size_t n_pin_loci{my_parameters.get_n_pin_loci()};
  const size_t n_sil_loci{my_parameters.get_n_sil_loci()};
  const int n_generations{my_parameters.get_n_generations()};
  const int population_size{my_parameters.get_population_size()};
  const int max_genetic_distance{my_parameters.get_max_genetic_distance()};
  const double pin_mutation_rate{my_parameters.get_pin_mutation_rate()};
  const double sil_mutation_rate{my_parameters.get_sil_mutation_rate()};
  const int rng_seed{my_parameters.get_rng_seed()};
  const int sampling_interval{my_parameters.get_sampling_interval()};

  std::mt19937 rng_engine{rng_seed};
  std::uniform_int_distribution<int> population_indices(0,population_size-1);
  std::uniform_int_distribution<int> pin_index(0, n_pin_loci - 1);
  std::uniform_int_distribution<int> sil_index(0, n_sil_loci - 1);
  std::uniform_int_distribution<unsigned long> inherits_pin_from_mother(0,(1 << n_pin_loci) - 1); //Must be of same data type as boost::dynamic_bitset second constructor argument
  std::uniform_int_distribution<unsigned long> inherits_sil_from_mother(0,(1 << n_sil_loci) - 1); //Must be of same data type as boost::dynamic_bitset second constructor argument
  std::uniform_real_distribution<double> chance(0.0, 1.0);
  std::vector<individual> population(
    population_size,
    individual(
      individual::pin_t(std::string(n_pin_loci,'A')),
      individual::sil_t(n_sil_loci,0b00000)
    )
  );

  //Overlapping generations
  for (int t{0}; t!=n_generations; ++t)
  {
    if (t % sampling_interval == 0)
    {
      my_results.add_measurement(
        t, population, max_genetic_distance
      );
    }
    const int random_father_index{population_indices(rng_engine)};
    const int random_mother_index{population_indices(rng_engine)};
    if (get_genetic_distance(population[random_mother_index], population[random_father_index]) > max_genetic_distance)
    {
      --t;
      continue;
    }
    const boost::dynamic_bitset<> pin_inheritance{n_pin_loci, inherits_pin_from_mother(rng_engine)};
    const boost::dynamic_bitset<> sil_inheritance{n_sil_loci, inherits_sil_from_mother(rng_engine)};
    const int random_kid_index{population_indices(rng_engine)};
    auto kid = create_offspring(
      population[random_mother_index],
      population[random_father_index],
      pin_inheritance,
      sil_inheritance
    );
    if (chance(rng_engine) < sil_mutation_rate) {
      kid.get_sil().flip(sil_index(rng_engine));
    }
    if (chance(rng_engine) < pin_mutation_rate) {
      kid.get_pin().change(pin_index(rng_engine), rng_engine);
    }
    population[random_kid_index] = kid;
  }

  //Save the results to file
  std::ofstream f(my_parameters.get_filename_genotype_frequency_graph());
  //my_results.summarize_genotypes(); //Unless you want the genotypes
  f << my_results;
}

void do_simulation_cpp(
  const int max_genetic_distance,
  const int n_generations,
  const int n_sil, //Use int over std::size_t for r
  const int n_pin, //Use int over std::size_t for r
  const double pin_mutation_rate,
  const int population_size,
  const std::string& results_genotype_frequency_graph_filename,
  const int rng_seed,
  const int sampling_interval,
  const double sil_mutation_rate
)
{
  const parameters p(
    max_genetic_distance,
    n_generations,
    n_pin,
    n_sil,
    pin_mutation_rate,
    population_size,
    results_genotype_frequency_graph_filename,
    rng_seed,
    sampling_interval,
    sil_mutation_rate
  );
  do_simulation(p);
}

