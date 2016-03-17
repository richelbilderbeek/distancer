#include "abundances.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

abundances::abundances(
  const std::vector<int>& individuals_per_species,
  const int t
) : m_individuals_per_species{individuals_per_species},
    m_t{t}
{
  if (m_t < 0)
  {
    std::stringstream msg;
    msg << __func__ << ": generation 't' cannot be "
      << "negative, value supplied is " << m_t
    ;
    throw std::invalid_argument(msg.str());
  }
  for (const auto n_individuals: individuals_per_species)
  {
    if (n_individuals < 0)
    {
      std::stringstream msg;
      msg << __func__ << ": number of individuals cannot be "
        << "negative, value supplied is " << n_individuals
      ;
      throw std::invalid_argument(msg.str());
    }
  }
}


std::ostream& operator<<(std::ostream& os, const abundances& r) noexcept
{
  std::stringstream s;
  s << r.m_t << ", ";
  for (const auto n: r.m_individuals_per_species)
  {
    s << n << ", ";
  }
  std::string t{s.str()};
  //Remove trailing comma and space
  if (!t.empty()) { t.pop_back(); }
  if (!t.empty()) { t.pop_back(); }
  os << t;
  return os;
}
