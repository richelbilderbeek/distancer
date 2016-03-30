#include "measurement.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

measurement::measurement(
  const int t,
  const std::vector<individual>& population,
  const int max_genetic_distance
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
  count_
}


std::ostream& operator<<(std::ostream& os, const measurement& r) noexcept
{
  std::stringstream s;
  s << r.m_t << ", ";
  for (const auto n: r.m_individuals_per_species)
  {
    s << n << ", ";
  }
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
  return os;
}
