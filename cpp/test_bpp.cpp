#ifdef REALLY_USE_BPP
#include <boost/test/unit_test.hpp>
#include <fstream>
//#include "simulation.h"

#include <Bpp/Seq/Alphabet.all>
#include <Bpp/Seq/Sequence.h>

#include <Bpp/Phyl/Model/SubstitutionModel.h>
#include <Bpp/Phyl/Model/Nucleotide/JCnuc.h>
#include <Bpp/Phyl/Simulation/HomogeneousSequenceSimulator.h>


// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

BOOST_AUTO_TEST_CASE(test_bpp_1)
{
  const std::string name{"test"};
  const std::string dna{"ATGC"};
  const bpp::BasicSequence sequence(
    name, dna, &bpp::AlphabetTools::DNA_ALPHABET
  );
  BOOST_CHECK(name == sequence.getName());
  BOOST_CHECK(dna == sequence.toString());
  BOOST_CHECK(dna.size() == sequence.size());
}

BOOST_AUTO_TEST_CASE(test_create_offsping_bpp_basic_sequence)
{
  {
    const size_t n_loci{3};
    const bpp::BasicSequence p("mom", "AAA");
    const bpp::BasicSequence q("dad", "CCC");
    const boost::dynamic_bitset<> inherit_from_p(n_loci, 0b001);
    const bpp::BasicSequence kid = create_offspring(p, q, inherit_from_p);
    const bpp::BasicSequence kid_should_be("","CCA");
    BOOST_CHECK(kid.toString() == kid_should_be.toString());
  }
  {
    const size_t n_loci{4};
    const bpp::BasicSequence p("mom", "GGGG");
    const bpp::BasicSequence q("dad", "TTTT");
    const boost::dynamic_bitset<> inherit_from_p(n_loci, 0b0101);
    const bpp::BasicSequence kid = create_offspring(p, q, inherit_from_p);
    const bpp::BasicSequence kid_should_be("","TGTG");
    BOOST_CHECK(kid.toString() == kid_should_be.toString());
  }
  {
    const size_t n_loci{4};
    const bpp::BasicSequence p("mom", "GGGG");
    const bpp::BasicSequence q("dad", "TTTT");
    const boost::dynamic_bitset<> inherit_from_p(n_loci, 0b1010);
    const bpp::BasicSequence kid = create_offspring(p, q, inherit_from_p);
    const bpp::BasicSequence kid_should_be("","GTGT");
    BOOST_CHECK(kid.toString() == kid_should_be.toString());
  }
}

#pragma GCC diagnostic pop

#endif //REALLY_USE_BPP
