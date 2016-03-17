#include "results_row.h"
#include <iostream>

results_row::results_row(
  const int n_individuals,
  const int t
) : m_n_individuals{n_individuals},
    m_t{t}
{

}


std::ostream& operator<<(std::ostream& os, const results_row& r) noexcept
{
  os << r.m_t << ", " << r.m_n_individuals;
  return os;
}
