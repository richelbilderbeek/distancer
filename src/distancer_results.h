#ifndef RESULTS_H
#define RESULTS_H

#include <iosfwd>
#include <vector>
#include "distancer_individual.h"
#include "distancer_sil_frequency_phylogeny.h"
#include "distancer_population.h"

class results
{
public:
  results();

  ///Measure the population at time t
  void add_measurement(
    const int t,
    const population& any_population,
    const int max_genetic_distance
  ) noexcept;

  sil_frequency_phylogeny get_sil_frequency_phylogeny() const { return m_sil_frequency_phylogeny; }

private:
  sil_frequency_phylogeny m_sil_frequency_phylogeny;

  //The vertex descriptors of the previous generation
  std::vector<sil_frequency_vertex_descriptor> m_vds_prev;


  friend std::ostream& operator<<(std::ostream& os, const results& r) noexcept;
};

std::ostream& operator<<(std::ostream& os, const results& r) noexcept;

#endif // RESULTS_H
