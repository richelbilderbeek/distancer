#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <boost/dynamic_bitset.hpp>

using individual = boost::dynamic_bitset<>;

///Count the number of ring species, where two individuals must have at most 'max_genetic_distance'
///genetic difference to be called the same species
std::vector<int> count_abundances(
  std::vector<individual> p,
  const int max_genetic_distance
) noexcept;

///Count the number of ring species, where two individuals must have at most 'max_genetic_distance'
///genetic difference to be called the same species
int count_species(std::vector<individual> p, const int max_genetic_distance) noexcept;

///Counts the number of loci that are different
int get_genetic_distance(
  const individual& a,
  const individual& b
) noexcept;

#endif // INDIVIDUAL_H
