#include <fstream>
#include "distancer.h"

#define BOOST_TEST_MODULE distancer
#include <boost/test/unit_test.hpp>

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

BOOST_AUTO_TEST_SUITE(test_helper_functions)

BOOST_AUTO_TEST_CASE(boost_dynamic_bitset)
{
  {
    const size_t n_loci{3};
    boost::dynamic_bitset<> p(n_loci, 0b001);
    BOOST_CHECK(p.count() == 1);
    boost::dynamic_bitset<> q(n_loci, 0b100);
    BOOST_CHECK(q.size() == p.size());
    BOOST_CHECK(q.count() == 1);
    boost::dynamic_bitset<> r = p ^ q;
    BOOST_CHECK(r.count() == 2);

    boost::dynamic_bitset<> inherit_from_p(n_loci, 0b001);

    boost::dynamic_bitset<> kid = (inherit_from_p & p) | (~inherit_from_p & q);

    boost::dynamic_bitset<> kid_should_be(n_loci, 0b101);
    BOOST_CHECK(kid == kid_should_be);
  }
  {
    const size_t n_loci{4};
    boost::dynamic_bitset<> p(n_loci, 0b0000);
    boost::dynamic_bitset<> q(n_loci, 0b1111);
    boost::dynamic_bitset<> inherit_from_p(n_loci, 0b0101);
    boost::dynamic_bitset<> kid = (inherit_from_p & p) | (~inherit_from_p & q);
    boost::dynamic_bitset<> kid_should_be(n_loci, 0b1010);
    BOOST_CHECK(kid == kid_should_be);
  }
  {
    const size_t n_loci{4};
    boost::dynamic_bitset<> p(n_loci, 0b1111);
    boost::dynamic_bitset<> q(n_loci, 0b0000);
    boost::dynamic_bitset<> inherit_from_p(n_loci, 0b0101);
    boost::dynamic_bitset<> kid = (inherit_from_p & p) | (~inherit_from_p & q);
    boost::dynamic_bitset<> kid_should_be(n_loci, 0b0101);
    BOOST_CHECK(kid == kid_should_be);

  }
  {
    const size_t n_loci{4};
    boost::dynamic_bitset<> p(n_loci, 0b1111);
    p.flip(2); //From right
    boost::dynamic_bitset<> p_should_be(n_loci, 0b1011);
    BOOST_CHECK(p == p_should_be);

  }
  {
    const size_t n_loci{4};
    boost::dynamic_bitset<> p(n_loci, 0b0000);
    p.flip(2); //From right
    boost::dynamic_bitset<> p_should_be(n_loci, 0b0100);
    BOOST_CHECK(p == p_should_be);
  }
  {
    const size_t n_loci{4};
    boost::dynamic_bitset<> p(n_loci, 15);
    boost::dynamic_bitset<> p_should_be(n_loci, 0b1111);
    BOOST_CHECK(p == p_should_be);
  }
  {
    const size_t n_loci{4};
    boost::dynamic_bitset<> p(n_loci, 7);
    boost::dynamic_bitset<> p_should_be(n_loci, 0b0111);
    BOOST_CHECK(p == p_should_be);
  }
}

BOOST_AUTO_TEST_CASE(test_count_abundances)
{
  {
    std::vector<boost::dynamic_bitset<>> p {
      boost::dynamic_bitset<>(3,0b000)
    };
    const std::vector<int> expected = { 1 };
    const auto result = ::count_abundances(p,1);
    BOOST_CHECK(result == expected);
  }
  {
    std::vector<boost::dynamic_bitset<>> p {
      boost::dynamic_bitset<>(3,0b001),
      boost::dynamic_bitset<>(3,0b001)
    };
    const std::vector<int> expected = { 2 };
    const auto n_species = ::count_species(p,1);
    const auto result = ::count_abundances(p,1);
    BOOST_CHECK(n_species == 1);
    BOOST_CHECK(result == expected);
  }
  {
    std::vector<boost::dynamic_bitset<>> p {
      boost::dynamic_bitset<>(3,0b010),
      boost::dynamic_bitset<>(3,0b010),
      boost::dynamic_bitset<>(3,0b010)
    };
    const std::vector<int> expected = { 3 };
    const auto n_species = ::count_species(p,1);
    const auto result = ::count_abundances(p,1);
    BOOST_CHECK(n_species == 1);
    BOOST_CHECK(result == expected);
  }
  {
    std::vector<boost::dynamic_bitset<>> p {
      boost::dynamic_bitset<>(3,0b100),
      boost::dynamic_bitset<>(3,0b110),
      boost::dynamic_bitset<>(3,0b010),
      boost::dynamic_bitset<>(3,0b011),
      boost::dynamic_bitset<>(3,0b001)
    };
    const std::vector<int> expected = { 5 };
    const auto result = ::count_abundances(p,1);
    BOOST_CHECK(result == expected);
  }
  {
    std::vector<boost::dynamic_bitset<>> p {
      boost::dynamic_bitset<>(3,0b100),
      boost::dynamic_bitset<>(3,0b001)
    };
    const std::vector<int> expected = { 1, 1 };
    const auto result = ::count_abundances(p,1);
    BOOST_CHECK(result == expected);
  }
}

BOOST_AUTO_TEST_CASE(test_count_connected_components)
{
  {
    boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> g;
    boost::add_vertex(g);
    BOOST_CHECK(::count_connected_components(g) == 1);
  }
  {
    boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> g;
    boost::add_vertex(g);
    boost::add_vertex(g);
    BOOST_CHECK(::count_connected_components(g) == 2);
  }
  {
    boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> g;
    const auto vd_a = boost::add_vertex(g);
    const auto vd_b = boost::add_vertex(g);
    boost::add_edge(vd_a, vd_b, g);
    BOOST_CHECK(::count_connected_components(g) == 1);
  }
}

BOOST_AUTO_TEST_CASE(count_species_boost)
{
  {
    std::vector<boost::dynamic_bitset<>> p {
      boost::dynamic_bitset<>(3,0b000)
    };
    BOOST_CHECK(::count_species(p,1) == 1);
  }
  {
    std::vector<boost::dynamic_bitset<>> p {
      boost::dynamic_bitset<>(3,0b001),
      boost::dynamic_bitset<>(3,0b001)
    };
    BOOST_CHECK(::count_species(p,1) == 1);
  }
  {
    std::vector<boost::dynamic_bitset<>> p {
      boost::dynamic_bitset<>(3,0b010),
      boost::dynamic_bitset<>(3,0b010),
      boost::dynamic_bitset<>(3,0b010)
    };
    BOOST_CHECK(::count_species(p,1) == 1);
  }
  {
    std::vector<boost::dynamic_bitset<>> p {
      boost::dynamic_bitset<>(3,0b100),
      boost::dynamic_bitset<>(3,0b110),
      boost::dynamic_bitset<>(3,0b010),
      boost::dynamic_bitset<>(3,0b011),
      boost::dynamic_bitset<>(3,0b001)
    };
    BOOST_CHECK(::count_species(p,1) == 1);
  }
  {
    std::vector<boost::dynamic_bitset<>> p {
      boost::dynamic_bitset<>(3,0b100),
      boost::dynamic_bitset<>(3,0b001)
    };
    BOOST_CHECK(::count_species(p,1) == 2);
  }
}

BOOST_AUTO_TEST_CASE(test_create_tally)
{
  {
    std::vector<int> v = {};
    std::vector<int> expected = {};
    const auto result = ::create_tally(v);
    BOOST_CHECK(result == expected);
  }
  {
    std::vector<int> v = {0};
    std::vector<int> expected = {1};
    const auto result = ::create_tally(v);
    BOOST_CHECK(result == expected);
  }
  {
    std::vector<int> v = {0,1,1,2,2,2};
    std::vector<int> expected = {1,2,3};
    const auto result = ::create_tally(v);
    BOOST_CHECK(result == expected);
  }
  {
    std::vector<int> v = {0,0,0};
    std::vector<int> expected = {3};
    const auto result = ::create_tally(v);
    BOOST_CHECK(result == expected);
  }
}

BOOST_AUTO_TEST_CASE(detect_by_travis)
{
  #ifndef NDEBUG
  std::ofstream f("test_debug.txt");
  #else
  std::ofstream f("test_release.txt");
  #endif
  f << "OK\n";
}


BOOST_AUTO_TEST_CASE(test_get_connected_components_ids)
{
  {
    boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> g;
    boost::add_vertex(g);
    const std::vector<int> expected = { 0 };
    const auto result = ::get_connected_components_ids(g);
    BOOST_CHECK(result == expected);
  }
  {
    boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> g;
    boost::add_vertex(g);
    boost::add_vertex(g);
    const std::vector<int> expected = { 0, 1 };
    const auto result = ::get_connected_components_ids(g);
    BOOST_CHECK(result == expected);
  }
  {
    boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> g;
    const auto vd_a = boost::add_vertex(g);
    const auto vd_b = boost::add_vertex(g);
    boost::add_edge(vd_a, vd_b, g);
    const std::vector<int> expected = { 0, 0 };
    const auto result = ::get_connected_components_ids(g);
    BOOST_CHECK(result == expected);
  }
}


BOOST_AUTO_TEST_CASE(get_genetic_distance_boost)
{
  const size_t n_loci{3};
  boost::dynamic_bitset<> a(n_loci, 0b000); //0b denotes binary
  boost::dynamic_bitset<> b(n_loci, 0b001);
  boost::dynamic_bitset<> c(n_loci, 0b011);
  BOOST_CHECK(::get_genetic_distance(a,a) == 0);
  BOOST_CHECK(::get_genetic_distance(b,b) == 0);
  BOOST_CHECK(::get_genetic_distance(a,b) == 1);
  BOOST_CHECK(::get_genetic_distance(b,a) == 1);
  BOOST_CHECK(::get_genetic_distance(c,a) == 2);
  BOOST_CHECK(::get_genetic_distance(a,c) == 2);
}

BOOST_AUTO_TEST_SUITE_END()

//Your code
#pragma GCC diagnostic pop
