#ifndef RESULTS_H
#define RESULTS_H

#include <iosfwd>
#include <vector>
#include "individual.h"
#include "measurement.h"

class results
{
public:
  results();

  ///Measure the population at time t
  void add_measurement(
    const int t,
    const std::vector<individual>& population,
    const int max_genetic_distance
  ) noexcept;

private:
  std::vector<std::pair<int,measurement>> m_measurements;

  friend std::ostream& operator<<(std::ostream& os, const results& r) noexcept;
};

std::ostream& operator<<(std::ostream& os, const results& r) noexcept;

#endif // RESULTS_H
