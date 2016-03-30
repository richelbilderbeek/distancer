#include "results.h"
#include <iostream>
#include <sstream>

results::results()
  : m_measurements{}
{

}

void results::add_measurement(
  const int t ,
  const std::vector<individual>& population,
  const int max_genetic_distance
) noexcept
{
  if (t < 0)
  {
    std::stringstream msg;
    msg << __func__ << ": generation 't' cannot be "
      << "negative, value supplied is " << t
    ;
    throw std::invalid_argument(msg.str());
  }
  m_measurements.push_back(
    measurement(population, max_genetic_distance)
  );
}

std::ostream& operator<<(std::ostream& os, const results& r) noexcept
{
  std::copy(
    std::begin(r.m_measurements),
    std::end(r.m_measurements),
    std::ostream_iterator<measurement>(os, "\n")
  );
  //?Newline is required by R's read.table function
  return os;
}
