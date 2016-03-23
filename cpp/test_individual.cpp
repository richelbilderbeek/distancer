#include "individual.h"
#include <fstream>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "helper.h"

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

BOOST_AUTO_TEST_CASE(test_create_offsping_individual)
{
  {
    const size_t n_loci{3};
    const individual p(n_loci, 0b001);
    const individual q(n_loci, 0b100);
    const boost::dynamic_bitset<> inherit_from_p(n_loci, 0b001);
    const individual kid = create_offspring(p, q, inherit_from_p);
    const individual kid_should_be(n_loci, 0b101);
    BOOST_CHECK(kid == kid_should_be);
  }
  {
    const size_t n_loci{4};
    const individual p(n_loci, 0b0000);
    const individual q(n_loci, 0b1111);
    const boost::dynamic_bitset<> inherit_from_p(n_loci, 0b0101);
    const individual kid = create_offspring(p, q, inherit_from_p);
    const individual kid_should_be(n_loci, 0b1010);
    BOOST_CHECK(kid == kid_should_be);
  }
  {
    const size_t n_loci{4};
    const individual p(n_loci, 0b1111);
    const individual q(n_loci, 0b0000);
    const boost::dynamic_bitset<> inherit_from_p(n_loci, 0b0101);
    const individual kid = create_offspring(p, q, inherit_from_p);
    const individual kid_should_be(n_loci, 0b0101);
    BOOST_CHECK(kid == kid_should_be);
  }
}

BOOST_AUTO_TEST_CASE(test_individual_default_construction_n_loci_and_sil_value)
{
  const size_t n_loci{8};
  const individual i(n_loci);
  BOOST_CHECK(i.get_sil().size() == n_loci);
  BOOST_CHECK(i.get_sil().to_ulong() == 0);
}

BOOST_AUTO_TEST_CASE(test_individual_construction_n_loci_and_sil_value)
{
  const size_t n_loci{8};
  const size_t sil_value{0b00101010};
  BOOST_CHECK(sil_value == 42); //What did you expect? :-)
  const individual i(n_loci, sil_value);
  BOOST_CHECK(i.get_sil().size() == n_loci);
  BOOST_CHECK(i.get_sil().to_ulong() == sil_value);
}

BOOST_AUTO_TEST_CASE(test_individual_construction_from_sil_t)
{
  const size_t n_loci{8};
  const size_t sil_value{0b00101010};
  const individual::sil_t sil(n_loci, sil_value);
  BOOST_CHECK(sil_value == 42); //What did you expect? :-)
  const individual i(sil);
  BOOST_CHECK(i.get_sil().size() == n_loci);
  BOOST_CHECK(i.get_sil().to_ulong() == sil_value);
}

BOOST_AUTO_TEST_CASE(test_individual_operator_equals)
{
  const size_t n_loci{8};
  const individual a(n_loci, 1);
  const individual b(n_loci, 1);
  const individual c(n_loci, 2);
  BOOST_CHECK(a == a);
  BOOST_CHECK(a == b);
  BOOST_CHECK(a != c);
  BOOST_CHECK(b == a);
  BOOST_CHECK(b == b);
  BOOST_CHECK(b != c);
  BOOST_CHECK(c != a);
  BOOST_CHECK(c != b);
  BOOST_CHECK(c == c);
}



BOOST_AUTO_TEST_CASE(test_count_abundances)
{
  {
    std::vector<individual> p {
      individual(3,0b000)
    };
    const std::vector<int> expected = { 1 };
    const auto result = ::count_abundances(p,1);
    BOOST_CHECK(result == expected);
  }
  {
    std::vector<individual> p {
      individual(3,0b001),
      individual(3,0b001)
    };
    const std::vector<int> expected = { 2 };
    const auto n_species = ::count_species(p,1);
    const auto result = ::count_abundances(p,1);
    BOOST_CHECK(n_species == 1);
    BOOST_CHECK(result == expected);
  }
  {
    std::vector<individual> p {
      individual(3,0b010),
      individual(3,0b010),
      individual(3,0b010)
    };
    const std::vector<int> expected = { 3 };
    const auto n_species = ::count_species(p,1);
    const auto result = ::count_abundances(p,1);
    BOOST_CHECK(n_species == 1);
    BOOST_CHECK(result == expected);
  }
  {
    std::vector<individual> p {
      individual(3,0b100),
      individual(3,0b110),
      individual(3,0b010),
      individual(3,0b011),
      individual(3,0b001)
    };
    const std::vector<int> expected = { 5 };
    const auto result = ::count_abundances(p,1);
    BOOST_CHECK(result == expected);
  }
  {
    std::vector<individual> p {
      individual(3,0b100),
      individual(3,0b001)
    };
    const std::vector<int> expected = { 1, 1 };
    const auto result = ::count_abundances(p,1);
    BOOST_CHECK(result == expected);
  }
}

BOOST_AUTO_TEST_CASE(count_species_boost)
{
  {
    std::vector<individual> p {
      individual(3,0b000)
    };
    BOOST_CHECK(::count_species(p,1) == 1);
  }
  {
    std::vector<individual> p {
      individual(3,0b001),
      individual(3,0b001)
    };
    BOOST_CHECK(::count_species(p,1) == 1);
  }
  {
    std::vector<individual> p {
      individual(3,0b010),
      individual(3,0b010),
      individual(3,0b010)
    };
    BOOST_CHECK(::count_species(p,1) == 1);
  }
  {
    std::vector<individual> p {
      individual(3,0b100),
      individual(3,0b110),
      individual(3,0b010),
      individual(3,0b011),
      individual(3,0b001)
    };
    BOOST_CHECK(::count_species(p,1) == 1);
  }
  {
    std::vector<individual> p {
      individual(3,0b100),
      individual(3,0b001)
    };
    BOOST_CHECK(::count_species(p,1) == 2);
  }
}

BOOST_AUTO_TEST_CASE(test_get_genetic_distance)
{
  const size_t n_loci{3};
  individual a(n_loci, 0b000); //0b denotes binary
  individual b(n_loci, 0b001);
  individual c(n_loci, 0b011);
  BOOST_CHECK(::get_genetic_distance(a,a) == 0);
  BOOST_CHECK(::get_genetic_distance(b,b) == 0);
  BOOST_CHECK(::get_genetic_distance(a,b) == 1);
  BOOST_CHECK(::get_genetic_distance(b,a) == 1);
  BOOST_CHECK(::get_genetic_distance(c,a) == 2);
  BOOST_CHECK(::get_genetic_distance(a,c) == 2);
}

#pragma GCC diagnostic pop

