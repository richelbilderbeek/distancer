#include "results.h"
#include <iostream>
#include <sstream>

results::results()
  : m_max_n_species{0},
    m_rows{}
{

}

void results::add_abundances(const abundances& row) noexcept
{
  m_max_n_species = std::max(m_max_n_species, row.get_n_species());
  m_rows.push_back(row);
}

std::ostream& operator<<(std::ostream& os, const results& r) noexcept
{
  const int max_n_species = r.m_max_n_species;
  //Header
  os << "t, ";
  for (int i=0; i!=max_n_species; ++i) {
    os << "n" << i;
    if (i + 1 != max_n_species) os << ", ";
  }
  os << '\n';
  //Rows
  const int n_rows = static_cast<int>(r.m_rows.size());
  for (int t{0}; t!=n_rows; ++t)
  {
    os << t << ", ";
    const auto row = r.m_rows[t];
    auto abundances = row.get_individuals_per_species();
    abundances.resize(max_n_species, 0);
    for (int i=0; i!=max_n_species; ++i)
    {
      os << abundances[i];
      if (i + 1 != max_n_species) os << ", ";
    }
    os << '\n';
  }
  //Newline is required by R's read.table function
  return os;
}
