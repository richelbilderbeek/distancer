#include "simulation.h"

#include <algorithm>
#include <fstream>
#include <random>
#include <boost/graph/isomorphism.hpp>
#include <Bpp/Seq/Alphabet.all>
#include "individual.h"
#include "results.h"
//#include "helper.h"


void do_simulation(const parameters& my_parameters)
{
  results my_results;
  const size_t n_pin_loci{my_parameters.get_n_pin_loci()};
  const size_t n_sil_loci{my_parameters.get_n_sil_loci()};
  const int n_generations{my_parameters.get_n_generations()};
  const int population_size{my_parameters.get_population_size()};
  const int max_genetic_distance{my_parameters.get_max_genetic_distance()};
  const double mutation_rate{my_parameters.get_mutation_rate()};
  const int rng_seed{my_parameters.get_rng_seed()};
  const int sampling_interval{my_parameters.get_sampling_interval()};

  std::mt19937 rng_engine{rng_seed};
  std::uniform_int_distribution<int> population_indices(0,population_size-1);
  std::uniform_int_distribution<int> pin_locus_index(0, n_pin_loci - 1);
  std::uniform_int_distribution<int> sil_locus_index(0, n_sil_loci - 1);
  std::uniform_int_distribution<unsigned long> inherits_pin_from_mother(0,(1 << n_pin_loci) - 1); //Must be of same data type as boost::dynamic_bitset second constructor argument
  std::uniform_int_distribution<unsigned long> inherits_sil_from_mother(0,(1 << n_sil_loci) - 1); //Must be of same data type as boost::dynamic_bitset second constructor argument
  std::uniform_real_distribution<double> chance(0.0, 1.0);
  std::vector<individual> population(
    population_size,
    individual(
      individual::pin_t("",std::string(n_pin_loci,'A'), &bpp::AlphabetTools::DNA_ALPHABET),
      individual::sil_t(n_sil_loci,0b00000)
    )
  );

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
    const boost::dynamic_bitset<> pin_inheritance{n_pin_loci, inherits_pin_from_mother(rng_engine)};
    const boost::dynamic_bitset<> sil_inheritance{n_sil_loci, inherits_sil_from_mother(rng_engine)};
    const int random_kid_index{population_indices(rng_engine)};
    auto kid = create_offspring(
      population[random_mother_index],
      population[random_father_index],
      pin_inheritance,
      sil_inheritance
    );
    if (chance(rng_engine) < mutation_rate) {
      kid.get_sil().flip(sil_locus_index(rng_engine));
    }
    population[random_kid_index] = kid;
  }


  std::ofstream f(my_parameters.get_results_filename());
  f << my_results;
}

void do_simulation_cpp(
  const int max_genetic_distance,
  const double mutation_rate,
  const int n_generations,
  const int n_sil, //Use int over std::size_t for r
  const int n_pin, //Use int over std::size_t for r
  const int population_size,
  const std::string& results_filename,
  const int rng_seed,
  const int sampling_interval
)
{
  const parameters p(
    max_genetic_distance,
    mutation_rate,
    n_generations,
    n_pin,
    n_sil,
    population_size,
    results_filename,
    rng_seed,
    sampling_interval
  );
  do_simulation(p);
}

