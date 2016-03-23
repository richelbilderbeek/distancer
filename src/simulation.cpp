#include "simulation.h"

#include <algorithm>
#include <fstream>
#include <random>
#include <boost/graph/isomorphism.hpp>
#include "individual.h"
#include "results.h"



void do_simulation(const parameters& my_parameters)
{
  results my_results;
  const size_t n_loci{my_parameters.get_n_loci()};
  const int n_generations{my_parameters.get_n_generations()};
  const int population_size{my_parameters.get_population_size()};
  const int max_genetic_distance{my_parameters.get_max_genetic_distance()};
  const double mutation_rate{my_parameters.get_mutation_rate()};
  const int rng_seed{my_parameters.get_rng_seed()};
  const int sampling_interval{my_parameters.get_sampling_interval()};

  std::mt19937 rng_engine{rng_seed};
  std::uniform_int_distribution<int> population_indices(0,population_size-1);
  std::uniform_int_distribution<int> locus_index(0,n_loci-1);
  std::uniform_int_distribution<unsigned long> inherits_from_mother(0,(1 << n_loci) - 1); //Must be of same data type as boost::dynamic_bitset second constructor argument
  std::uniform_real_distribution<double> chance(0.0, 1.0);
  std::vector<individual> population(population_size, individual(n_loci));

  //Overlapping generations
  for (int t{0}; t!=n_generations; ++t)
  {
    if (t % sampling_interval == 0)
    {
      my_results.add_abundances(
        t,
        abundances(
          count_abundances(population, max_genetic_distance),
          t
        )
      );
    }
    const int random_father_index{population_indices(rng_engine)};
    const int random_mother_index{population_indices(rng_engine)};
    if (get_genetic_distance(population[random_mother_index], population[random_father_index]) > max_genetic_distance)
    {
      --t;
      continue;
    }
    const boost::dynamic_bitset<> inheritance{n_loci, inherits_from_mother(rng_engine)};
    const int random_kid_index{population_indices(rng_engine)};
    individual::sil_t sil{
        ( inheritance & population[random_mother_index].get_sil())
      | (~inheritance & population[random_father_index].get_sil())
    };
    if (chance(rng_engine) < mutation_rate) {
      sil.flip(locus_index(rng_engine));
    }
    population[random_kid_index] = individual(sil);
  }

  std::ofstream f("results.csv");
  f << my_results;
}

//' The function that does a simulation.
//' @param max_genetic_distance the maximum number of different loci that two individuals can still produce viable offspring with
//' @param mutation_rate DNA mutation rate
//' @param n_generations number of generations
//' @param n_loci number of loci
//' @param population_size population size
//' @param rng_seed random number generator seed
//' @param sampling_interval after how many generations is the population sampled for species abundances
//' @return Nothing
//' @export
// [[Rcpp::export]]
void do_simulation_cpp(
  const int max_genetic_distance,
  const double mutation_rate,
  const int n_generations,
  const int n_loci, //Use int over std::size_t for r
  const int population_size,
  const int rng_seed,
  const int sampling_interval
)
{
  const parameters p(
    max_genetic_distance,
    mutation_rate,
    n_generations,
    n_loci,
    population_size,
    rng_seed,
    sampling_interval
  );
  do_simulation(p);
}

