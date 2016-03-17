#ifndef RESULTS_H
#define RESULTS_H

#include <iosfwd>
#include <vector>
#include "abundances.h"

class results
{
public:
  results();
  void add_abundances(const abundances& row) noexcept;

private:
  int m_max_n_species;
  std::vector<abundances> m_rows;

  friend std::ostream& operator<<(std::ostream& os, const results& r) noexcept;
};

std::ostream& operator<<(std::ostream& os, const results& r) noexcept;

#endif // RESULTS_H
