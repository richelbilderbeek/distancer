#include "results.h"
#include <iostream>
#include <sstream>

results::results()
  : m_max_n_species{0},
    m_measurements{}
{

}

void results::add_measurement(
  const int t,
  const std::vector<individual>& population,
  const int max_genetic_distance
) noexcept
{
  m_measurements.push_back(
    std::make_pair(
      t,
      measurement(t, population, max_genetic_distance)
    )
  );
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
    os << r.m_rows[t].first << ", ";
    const auto row = r.m_rows[t].second;
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
