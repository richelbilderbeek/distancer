#ifndef ABUNDANCES_H
#define ABUNDANCES_H

#include <iosfwd>
#include <string>
#include "individual.h"
#include <vector>

class measurement
{
public:
  measurement(
    const int t,
    const std::vector<individual>& population,
    const int max_genetic_distance
  );

private:
  std::vector<int> m_individuals_per_species;
  int m_t;

  friend std::ostream& operator<<(std::ostream& os, const measurement& r) noexcept;
};

std::ostream& operator<<(std::ostream& os, const measurement& r) noexcept;

#endif // ABUNDANCES_H
