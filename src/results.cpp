#include "results.h"
#include <iostream>
#include <sstream>

results::results()
  : m_rows{}
{

}

void results::add_row(const results_row& row) noexcept
{
  m_rows.push_back(row);
}

std::ostream& operator<<(std::ostream& os, const results& r) noexcept
{
  os << results_row::get_header() << '\n';
  for (const auto row: r.m_rows) {
    os << row << '\n';
  }
  return os;
}
