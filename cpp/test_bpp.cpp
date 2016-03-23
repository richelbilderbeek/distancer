#include <boost/test/unit_test.hpp>
#include <fstream>
//#include "simulation.h"

//#define BOOST_TEST_MODULE distancer

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

BOOST_AUTO_TEST_CASE(test_bpp_2)
{
  /*
  const bpp::JCnuc jc(&bpp::AlphabetTools::DNA_ALPHABET);
  const std::string name{"test"};
  const std::string dna{"AAAAAAAAAA"};
  bpp::BasicSequence sequence(
    name, dna, &bpp::AlphabetTools::DNA_ALPHABET
  );
  bpp::HomogeneousSequenceSimulator sim(
    &sequence
    &jc,
    0.001, //Mutation rate per nucleotide per DNA replication
    100000 //Number of DNA replications
  );

  BOOST_CHECK("AAAAAAAAAA" != sequence.toString()); //Sequence should have changed
  */
}

#pragma GCC diagnostic pop

