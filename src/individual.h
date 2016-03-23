#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <boost/dynamic_bitset.hpp>

struct individual
{
  using sil_t = boost::dynamic_bitset<>;
  individual(const size_t n_loci, const size_t sil_value = 0);
  individual(const sil_t& sil);

  const sil_t& get_sil() const noexcept { return m_sil; }
        sil_t& get_sil()       noexcept { return m_sil; }

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
  const boost::dynamic_bitset<>& inherit_from_p
);

///Counts the number of loci that are different
int get_genetic_distance(
  const individual& a,
  const individual& b
) noexcept;

bool operator==(const individual& lhs, const individual& rhs) noexcept;
bool operator!=(const individual& lhs, const individual& rhs) noexcept;

#endif // INDIVIDUAL_H
