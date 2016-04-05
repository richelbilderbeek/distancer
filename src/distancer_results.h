#ifndef RESULTS_H
#define RESULTS_H

#include <iosfwd>
#include <vector>
#include "distancer_individual.h"
#include "distancer_measurement.h"
#include "distancer_results_graph.h"

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

  results_graph get_sil_frequency_phylogeny() const { return {}; }

private:
  std::vector<measurement> m_measurements;

  friend std::ostream& operator<<(std::ostream& os, const results& r) noexcept;
};

std::ostream& operator<<(std::ostream& os, const results& r) noexcept;

#endif // RESULTS_H
