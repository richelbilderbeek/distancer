#include "distancer.h"

#include <algorithm>
#include <fstream>
#include <random>
#include <boost/graph/isomorphism.hpp>
#include "results.h"

std::vector<int> count_abundances(
  std::vector<boost::dynamic_bitset<>> p,
  const int max_genetic_distance
) noexcept
{
  if (p.empty()) return {};

  const int sz{static_cast<int>(p.size())};
  if (sz == 1) return { static_cast<int>(p.size()) };

  boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> g(sz);

  for (int i=0; i!=sz; ++i)
  {
    for (int j=i+1; j!=sz; ++j)
    {
      const int genetic_distance{get_genetic_distance(p[i],p[j])};
      if (genetic_distance <= max_genetic_distance)
      {
        const auto vip = vertices(g);
        auto from_iter = vip.first + i;
        auto to_iter = vip.first + j;
        boost::add_edge(*from_iter, *to_iter, g);
      }
    }
  }
  const auto ids = get_connected_components_ids(g);
  return create_tally(ids);
}

int count_species(std::vector<boost::dynamic_bitset<>> p, const int max_genetic_distance) noexcept
{
  //const bool debug{false};
  if (p.empty()) return 0;

  //Ditch the duplicates to speed up the calculation
  std::sort(std::begin(p),std::end(p), [](const boost::dynamic_bitset<>& lhs, const boost::dynamic_bitset<>& rhs) { return lhs.to_ulong() < rhs.to_ulong(); } );
  typename std::vector<boost::dynamic_bitset<>>::iterator new_end = std::unique(std::begin(p),std::end(p));
  p.erase(new_end,std::end(p));

  const int sz{static_cast<int>(p.size())};
  if (sz == 1) return 1;

  boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> g(sz);

  for (int i=0; i!=sz; ++i)
  {
    for (int j=i+1; j!=sz; ++j)
    {
      const int genetic_distance{get_genetic_distance(p[i],p[j])};
      if (genetic_distance <= max_genetic_distance)
      {
        const auto vip = vertices(g);
        auto from_iter = vip.first + i;
        auto to_iter = vip.first + j;
        boost::add_edge(*from_iter, *to_iter, g);
      }
    }
  }
  return count_connected_components(g);
}

std::vector<int> create_tally(const std::vector<int>& v) noexcept
{
  std::map<int, int> m;
  for (const auto i: v)
  {
    const auto iter = m.find(i);
    if (iter == std::end(m))
    {
      m.insert(std::make_pair(i, 1));
    }
    else { ++m[i]; }
  }

  std::vector<int> t;
  t.reserve(m.size());
  for (const auto p: m) {
    t.push_back(p.second);
  }
  return t;
}

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
  std::vector<boost::dynamic_bitset<>> population(population_size, boost::dynamic_bitset<>(n_loci));

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
    population[random_kid_index] = (inheritance & population[random_mother_index]) | (~inheritance & population[random_father_index]);
    if (chance(rng_engine) < mutation_rate) {
      population[random_kid_index].flip(locus_index(rng_engine));
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

///Counts the number of loci that are different
int get_genetic_distance(
  const boost::dynamic_bitset<>& a,
  const boost::dynamic_bitset<>& b
) noexcept
{
  const boost::dynamic_bitset<> d = a ^ b;
  return d.count();
}
