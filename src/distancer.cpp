#include "distancer.h"

#include <algorithm>
#include <fstream>
#include <random>
#include <boost/graph/isomorphism.hpp>
#include "results.h"

///Count the number of ring species, where two individuals must have at most 'max_genetic_distance'
///genetic difference to be called the same species
int count_species(std::vector<boost::dynamic_bitset<>> p, const int max_genetic_distance) noexcept
{
  //const bool debug{false};
  if (p.empty()) return 0;
  std::sort(std::begin(p),std::end(p), [](const boost::dynamic_bitset<>& lhs, const boost::dynamic_bitset<>& rhs) { return lhs.to_ulong() < rhs.to_ulong(); } );
  typename std::vector<boost::dynamic_bitset<>>::iterator new_end = std::unique(std::begin(p),std::end(p));
  p.erase(new_end,std::end(p));

  const int sz{static_cast<int>(p.size())};
  if (sz == 1) return 1;

  boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> g(sz);
  //assert(sz == static_cast<int>(boost::num_vertices(g)));

  for (int i=0; i!=sz; ++i)
  {
    //if (debug) { std::cout << "i (" << i << ") has genome " << p[i] << '\n'; }
    for (int j=i+1; j!=sz; ++j)
    {
      //assert(j < sz);
      const int genetic_distance{get_genetic_distance(p[i],p[j])};
      //if (debug) { std::cout << "j (" << j << ") has genome " << p[j] << " and genetic distance " << genetic_distance << '\n'; }
      if (genetic_distance <= max_genetic_distance)
      {
        //if (debug) { std::cout << "MATCH\n"; }
        const auto vip = vertices(g);
        auto from_iter = vip.first + i;
        auto to_iter = vip.first + j;
        boost::add_edge(*from_iter, *to_iter, g);
      }
      else
      {
        //if (debug) { std::cout << "No match\n"; }
      }
    }
  }
  return count_connected_components(g);
}

void do_simulation(const parameters& my_parameters)
{
  results my_results;
  my_results.add_row(results_row(1,0)); //There is one species at t is zero
  const size_t n_loci{my_parameters.get_n_loci()};
  const int rng_seed{my_parameters.get_rng_seed()};
  const int n_generations{my_parameters.get_n_generations()};
  const int population_size{my_parameters.get_population_size()};
  const int max_genetic_distance{my_parameters.get_max_genetic_distance()};
  const double mutation_rate{my_parameters.get_mutation_rate()};

  std::mt19937 rng_engine{rng_seed};
  std::uniform_int_distribution<int> population_indices(0,population_size-1);
  std::uniform_int_distribution<int> locus_index(0,n_loci-1);
  std::uniform_int_distribution<unsigned long> inherits_from_mother(0,(1 << n_loci) - 1); //Must be of same data type as boost::dynamic_bitset second constructor argument
  std::uniform_real_distribution<double> chance(0.0, 1.0);
  std::vector<boost::dynamic_bitset<>> population(population_size, boost::dynamic_bitset<>(n_loci));

  //assert(count_species(population,2) == 1);
  int max_species_observed = 1;

  //Overlapping generations
  for (int i=0; i!=n_generations; ++i)
  {
    const int random_father_index{population_indices(rng_engine)};
    const int random_mother_index{population_indices(rng_engine)};
    if (get_genetic_distance(population[random_mother_index], population[random_father_index]) > max_genetic_distance)
    {
      --i;
      continue;
    }
    const boost::dynamic_bitset<> inheritance{n_loci, inherits_from_mother(rng_engine)};
    const int random_kid_index{population_indices(rng_engine)};
    //assert(population[random_mother_index].size() == population[random_father_index].size());
    population[random_kid_index] = (inheritance & population[random_mother_index]) | (~inheritance & population[random_father_index]);
    if (chance(rng_engine) < mutation_rate) {
      population[random_kid_index].flip(locus_index(rng_engine));
    }

    if (count_species(population,max_genetic_distance) > max_species_observed)
    {
      max_species_observed = count_species(population,max_genetic_distance);
      //std::cout << i << ": " << count_species(population,max_genetic_distance) << '\n';
      //for (const auto individual: population) { std::cout << individual << " "; }
      //std::cout << "\n";
      my_results.add_row(results_row(max_species_observed, i));
      if (max_species_observed == 6) break;
    }
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
//' @return Nothing
//' @export
// [[Rcpp::export]]
void do_simulation_cpp(
  const int max_genetic_distance,
  const double mutation_rate,
  const int n_generations,
  const int n_loci, //Use int over std::size_t for r
  const int population_size,
  const int rng_seed
)
{
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

///Counts the number of loci that are different
int get_genetic_distance(
  const boost::dynamic_bitset<>& a,
  const boost::dynamic_bitset<>& b
) noexcept
{
  const boost::dynamic_bitset<> d = a ^ b;
  return d.count();
}
