#ifndef RESULTS_H
#define RESULTS_H

#include <iosfwd>
#include <vector>
#include "results_row.h"

class results
{
public:
  results();
  void add_row(const results_row& row) noexcept;

private:
  std::vector<results_row> m_rows;

  friend std::ostream& operator<<(std::ostream& os, const results& r) noexcept;
};

std::ostream& operator<<(std::ostream& os, const results& r) noexcept;

#endif // RESULTS_H
