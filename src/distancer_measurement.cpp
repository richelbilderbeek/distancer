#include "distancer_measurement.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

measurement::measurement(
  const std::vector<individual>& population,
  const int max_genetic_distance
)
  : m_n_possible_species{count_possible_species(population, max_genetic_distance)},
    m_n_species{count_species(population, max_genetic_distance)}
{
  //TODO: do upper calculations at the same time
}


std::ostream& operator<<(std::ostream& os, const measurement& /* r */) noexcept
{
  /*
  std::stringstream s;
  //s << r.m_t << ", ";
  //for (const auto n: r.m_individuals_per_species)
  //{
  //  s << n << ", ";
  //}
  std::string t{s.str()};
  //Remove trailing comma and space
  if (!t.empty())
  {
    //t.pop_back(); //Does not work under Travis
    t.resize(t.size() - 1);
  }
  if (!t.empty())
  {
    //t.pop_back(); //Does not work under Travis
    t.resize(t.size() - 1);
  }
  os << t;
  */
  return os;
}
