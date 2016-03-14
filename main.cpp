#include <algorithm>
#include <cassert>
#include <iostream>
#include <bitset>
#include <random>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/isomorphism.hpp>
#include <boost/graph/connected_components.hpp>

void test() noexcept;

///Counts the number of components in a graph
///For example: A-B C-D would a graph of two edges, four vertices and two connected component
template <typename graph>
int count_connected_components(
  const graph& g
) noexcept
{
  const bool debug{false};
  std::vector<int> c(boost::num_vertices(g));
  const int n = boost::connected_components(g,
    boost::make_iterator_property_map(
      std::begin(c),
      get(boost::vertex_index, g)
    )
  );

  if (debug) {
    std::copy(std::begin(c),std::end(c),std::ostream_iterator<int>(std::cout, ", "));
    std::cout << '\n';
  }
  return n;
}

///Counts the number of loci that are different
template <unsigned int n_loci>
int get_genetic_distance(
  const std::bitset<n_loci>& a,
  const std::bitset<n_loci>& b
) noexcept
{
  const std::bitset<n_loci> d = a ^ b;
  return d.count();
}


///Count the number of ring species, where two individuals must have at most 'max_genetic_distance'
///genetic difference to be called the same species
template <unsigned int n_loci>
int count_species(std::vector<std::bitset<n_loci>> p, const int max_genetic_distance) noexcept
{
  const bool debug{false};
  if (p.empty()) return 0;
  std::sort(std::begin(p),std::end(p), [](const std::bitset<n_loci>& lhs, const std::bitset<n_loci>& rhs) { return lhs.to_ulong() < rhs.to_ulong(); } );
  typename std::vector<std::bitset<n_loci>>::iterator new_end = std::unique(std::begin(p),std::end(p));
  p.erase(new_end,std::end(p));

  const int sz{static_cast<int>(p.size())};
  if (sz == 1) return 1;

  boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> g(sz);
  assert(sz == static_cast<int>(boost::num_vertices(g)));

  for (int i=0; i!=sz; ++i)
  {
    if (debug) { std::cout << "i (" << i << ") has genome " << p[i] << '\n'; }
    for (int j=i+1; j!=sz; ++j)
    {
      assert(j < sz);
      const int genetic_distance{get_genetic_distance(p[i],p[j])};
      if (debug) { std::cout << "j (" << j << ") has genome " << p[j] << " and genetic distance " << genetic_distance << '\n'; }
      if (genetic_distance <= max_genetic_distance)
      {
        if (debug) { std::cout << "MATCH\n"; }
        const auto vip = vertices(g);
        auto from_iter = vip.first + i;
        auto to_iter = vip.first + j;
        boost::add_edge(*from_iter, *to_iter, g);
      }
      else
      {
        if (debug) { std::cout << "No match\n"; }
      }
    }
  }


  return count_connected_components(g);
}

int main()
{
  test();
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
    }
  }

}


/* Output:

*/


void test() noexcept
{
  {
    const int n_loci{3};
    std::bitset<n_loci> a("000");
    std::bitset<n_loci> b("001");
    std::bitset<n_loci> c("011");
    assert(get_genetic_distance(a,a) == 0);
    assert(get_genetic_distance(b,b) == 0);
    assert(get_genetic_distance(a,b) == 1);
    assert(get_genetic_distance(b,a) == 1);
    assert(get_genetic_distance(c,a) == 2);
    assert(get_genetic_distance(a,c) == 2);
  }
  {
    std::vector<std::bitset<3>> p {
      std::bitset<3>("000")
    };
    assert(count_species(p,1) == 1);
  }
  {
    std::vector<std::bitset<3>> p {
      std::bitset<3>("001"),
      std::bitset<3>("001")
    };
    assert(count_species(p,1) == 1);
  }
  {
    std::vector<std::bitset<3>> p {
      std::bitset<3>("010"),
      std::bitset<3>("010"),
      std::bitset<3>("010")
    };
    assert(count_species(p,1) == 1);
  }
  {
    std::vector<std::bitset<3>> p {
      std::bitset<3>("100"),
      std::bitset<3>("110"),
      std::bitset<3>("010"),
      std::bitset<3>("011"),
      std::bitset<3>("001")
    };
    assert(count_species(p,1) == 1);
  }
  {
    std::vector<std::bitset<3>> p {
      std::bitset<3>("100"),
      std::bitset<3>("001")
    };
    assert(count_species(p,1) == 2);
  }
  {
    const int n_loci{3};
    std::bitset<n_loci> p("001");
    assert(p.count() == 1);
    std::bitset<n_loci> q("100");
    assert(q.size() == p.size());
    assert(q.count() == 1);
    std::bitset<n_loci> r = p ^ q;
    assert(r.count() == 2);

    std::bitset<n_loci> inherit_from_p("001");

    std::bitset<n_loci> kid = (inherit_from_p & p) | (~inherit_from_p & q);

    std::bitset<n_loci> kid_should_be("101");
    assert(kid == kid_should_be);
  }
  {
    const int n_loci{4};
    std::bitset<n_loci> p("0000");
    std::bitset<n_loci> q("1111");
    std::bitset<n_loci> inherit_from_p("0101");
    std::bitset<n_loci> kid = (inherit_from_p & p) | (~inherit_from_p & q);
    std::bitset<n_loci> kid_should_be("1010");
    assert(kid == kid_should_be);
  }
  {
    const int n_loci{4};
    std::bitset<n_loci> p("1111");
    std::bitset<n_loci> q("0000");
    std::bitset<n_loci> inherit_from_p("0101");
    std::bitset<n_loci> kid = (inherit_from_p & p) | (~inherit_from_p & q);
    std::bitset<n_loci> kid_should_be("0101");
    assert(kid == kid_should_be);

  }
  {
    const int n_loci{4};
    std::bitset<n_loci> p("1111");
    p.flip(2); //From right
    std::bitset<n_loci> p_should_be("1011");
    assert(p == p_should_be);

  }
  {
    const int n_loci{4};
    std::bitset<n_loci> p("0000");
    p.flip(2); //From right
    std::bitset<n_loci> p_should_be("0100");
    assert(p == p_should_be);
  }
  {
    const int n_loci{4};
    std::bitset<n_loci> p(15);
    std::bitset<n_loci> p_should_be("1111");
    assert(p == p_should_be);
  }
  {
    const int n_loci{4};
    std::bitset<n_loci> p(7);
    std::bitset<n_loci> p_should_be("0111");
    assert(p == p_should_be);
  }
}
