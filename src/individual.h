#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <iosfwd>
#include <boost/dynamic_bitset.hpp>
#include <Bpp/Seq/Sequence.h>

struct individual
{
  /// Species Identity Loci
  using sil_t = boost::dynamic_bitset<>;
  /// Phylogeny Inference Nucleotides
  using pin_t = bpp::BasicSequence;

  individual(
    const std::string& pin_sequence,
    const size_t n_loci,
    const size_t sil_value
  );
  individual(
    const pin_t& pin,
    const sil_t& sil
  );

  const pin_t& get_pin() const noexcept { return m_pin; }
        pin_t& get_pin()       noexcept { return m_pin; }

  const sil_t& get_sil() const noexcept { return m_sil; }
        sil_t& get_sil()       noexcept { return m_sil; }

  private:
  ///Phylogeny Inference Nucleotides: the neutral DNA
  ///use to infer phylogenies
  pin_t m_pin;

  ///Species Identity Loci: determines if an individual
  ///can produce viable offspring with others
  sil_t m_sil;

};


///Count the number of ring species, where two individuals must have at most 'max_genetic_distance'
///genetic difference to be called the same species
std::vector<int> count_abundances(
  std::vector<individual> p,
  const int max_genetic_distance
) noexcept;

///Count the number of ring species, where two individuals must have at most 'max_genetic_distance'
///genetic difference to be called the same species
int count_species(std::vector<individual> p, const int max_genetic_distance) noexcept;

individual create_offspring(
  const individual& p,
  const individual& q,
  const boost::dynamic_bitset<>& inherit_pin_from_p,
  const boost::dynamic_bitset<>& inherit_sil_from_p
);

///Counts the number of loci that are different
int get_genetic_distance(
  const individual& a,
  const individual& b
) noexcept;

bool operator==(const individual& lhs, const individual& rhs) noexcept;
bool operator!=(const individual& lhs, const individual& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const individual& i) noexcept;

#endif // INDIVIDUAL_H
