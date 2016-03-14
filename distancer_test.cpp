#include <fstream>
#include "distancer.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE distancer
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(distancer_functions)

BOOST_AUTO_TEST_CASE(detect_by_travis)
{
  #ifndef NDEBUG
  std::ofstream f("test_debug.txt");
  #else
  std::ofstream f("test_release.txt");
  #endif
  f << "OK\n";
}

BOOST_AUTO_TEST_CASE(get_genetic_distance)
{
  const int n_loci{3};
  std::bitset<n_loci> a("000");
  std::bitset<n_loci> b("001");
  std::bitset<n_loci> c("011");
  BOOST_CHECK(::get_genetic_distance(a,a) == 0);
  BOOST_CHECK(::get_genetic_distance(b,b) == 0);
  BOOST_CHECK(::get_genetic_distance(a,b) == 1);
  BOOST_CHECK(::get_genetic_distance(b,a) == 1);
  BOOST_CHECK(::get_genetic_distance(c,a) == 2);
  BOOST_CHECK(::get_genetic_distance(a,c) == 2);
}

BOOST_AUTO_TEST_CASE(count_species)
{
  {
    std::vector<std::bitset<3>> p {
      std::bitset<3>("000")
    };
    BOOST_CHECK(::count_species(p,1) == 1);
  }
  {
    std::vector<std::bitset<3>> p {
      std::bitset<3>("001"),
      std::bitset<3>("001")
    };
    BOOST_CHECK(::count_species(p,1) == 1);
  }
  {
    std::vector<std::bitset<3>> p {
      std::bitset<3>("010"),
      std::bitset<3>("010"),
      std::bitset<3>("010")
    };
    BOOST_CHECK(::count_species(p,1) == 1);
  }
  {
    std::vector<std::bitset<3>> p {
      std::bitset<3>("100"),
      std::bitset<3>("110"),
      std::bitset<3>("010"),
      std::bitset<3>("011"),
      std::bitset<3>("001")
    };
    BOOST_CHECK(::count_species(p,1) == 1);
  }
  {
    std::vector<std::bitset<3>> p {
      std::bitset<3>("100"),
      std::bitset<3>("001")
    };
    BOOST_CHECK(::count_species(p,1) == 2);
  }
}



BOOST_AUTO_TEST_CASE(bitset)
{
  {
    const int n_loci{3};
    std::bitset<n_loci> p("001");
    BOOST_CHECK(p.count() == 1);
    std::bitset<n_loci> q("100");
    BOOST_CHECK(q.size() == p.size());
    BOOST_CHECK(q.count() == 1);
    std::bitset<n_loci> r = p ^ q;
    BOOST_CHECK(r.count() == 2);

    std::bitset<n_loci> inherit_from_p("001");

    std::bitset<n_loci> kid = (inherit_from_p & p) | (~inherit_from_p & q);

    std::bitset<n_loci> kid_should_be("101");
    BOOST_CHECK(kid == kid_should_be);
  }
  {
    const int n_loci{4};
    std::bitset<n_loci> p("0000");
    std::bitset<n_loci> q("1111");
    std::bitset<n_loci> inherit_from_p("0101");
    std::bitset<n_loci> kid = (inherit_from_p & p) | (~inherit_from_p & q);
    std::bitset<n_loci> kid_should_be("1010");
    BOOST_CHECK(kid == kid_should_be);
  }
  {
    const int n_loci{4};
    std::bitset<n_loci> p("1111");
    std::bitset<n_loci> q("0000");
    std::bitset<n_loci> inherit_from_p("0101");
    std::bitset<n_loci> kid = (inherit_from_p & p) | (~inherit_from_p & q);
    std::bitset<n_loci> kid_should_be("0101");
    BOOST_CHECK(kid == kid_should_be);

  }
  {
    const int n_loci{4};
    std::bitset<n_loci> p("1111");
    p.flip(2); //From right
    std::bitset<n_loci> p_should_be("1011");
    BOOST_CHECK(p == p_should_be);

  }
  {
    const int n_loci{4};
    std::bitset<n_loci> p("0000");
    p.flip(2); //From right
    std::bitset<n_loci> p_should_be("0100");
    BOOST_CHECK(p == p_should_be);
  }
  {
    const int n_loci{4};
    std::bitset<n_loci> p(15);
    std::bitset<n_loci> p_should_be("1111");
    BOOST_CHECK(p == p_should_be);
  }
  {
    const int n_loci{4};
    std::bitset<n_loci> p(7);
    std::bitset<n_loci> p_should_be("0111");
    BOOST_CHECK(p == p_should_be);
  }
}

BOOST_AUTO_TEST_SUITE_END()
