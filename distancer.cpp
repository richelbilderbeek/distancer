#include "distancer.h"

#include <algorithm>
#include <cassert>
#include <random>
#include <boost/graph/isomorphism.hpp>

void do_simulation()
{
  const int n_loci{16};
  const int rng_seed{42};
  const int n_generations{1000000000};
  const int population_size{8};
  const int max_genetic_distance{1};
  const double mutation_rate{0.1}; //Chance to have 1 locus flipped in a genome

  std::mt19937 rng_engine{rng_seed};
  std::uniform_int_distribution<int> population_indices(0,population_size-1);
  std::uniform_int_distribution<int> locus_index(0,n_loci-1);
  std::uniform_int_distribution<long long unsigned int> inherits_from_mother(0,(1 << n_loci) - 1);
  std::uniform_real_distribution<double> chance(0.0, 1.0);
  std::vector<std::bitset<n_loci>> p(population_size);
  assert(count_species(p,2) == 1);
  int max_species_observed = 1;

  //Overlapping generations
  for (int i=0; i!=n_generations; ++i)
  {
    const int random_father_index{population_indices(rng_engine)};
    const int random_mother_index{population_indices(rng_engine)};
    if (get_genetic_distance(p[random_mother_index], p[random_father_index]) > max_genetic_distance)
    {
      --i;
      continue;
    }
    const std::bitset<n_loci> inheritance{inherits_from_mother(rng_engine)};
    const int random_kid_index{population_indices(rng_engine)};
    p[random_kid_index] = (inheritance & p[random_mother_index]) | (~inheritance & p[random_father_index]);
    if (chance(rng_engine) < mutation_rate) {
      p[random_kid_index].flip(locus_index(rng_engine));
    }

    if (count_species(p,max_genetic_distance) > max_species_observed)
    {
      max_species_observed = count_species(p,max_genetic_distance);
      std::cout << i << ": " << count_species(p,max_genetic_distance) << '\n';
      for (const auto individual: p) { std::cout << individual << " "; }
      std::cout << "\n";

      if (max_species_observed == 6) return;
    }
  }
}
