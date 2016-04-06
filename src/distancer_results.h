#ifndef RESULTS_H
#define RESULTS_H

#include <iosfwd>
#include <vector>
#include "distancer_individual.h"
#include "distancer_sil_frequency_phylogeny.h"
#include "distancer_population.h"
#include "distancer_parameters.h"

class results
{
public:
  results(
    const int max_genetic_distance
  );

  ///Measure the population at time t
  void add_measurement(
    const int t,
    const population& any_population
  ) noexcept;

  sil_frequency_phylogeny get_sil_frequency_phylogeny() const { return m_sil_frequency_phylogeny; }

  ///Will summarize the sil_frequency_phylogeny, to be run after a simulation,
  ///as it used the last vertex descriptors
  ///(?but perhaps it can be called during a sim?)
  ///After 'summarize', call 'get_sil_frequency_phylogeny' again
  void summarize_genotypes();

private:
  int m_max_genetic_distance;

  sil_frequency_phylogeny m_sil_frequency_phylogeny;

  ///The vertex descriptors of the previous generation
  std::vector<sil_frequency_vertex_descriptor> m_vds_prev;

  friend std::ostream& operator<<(std::ostream& os, const results& r) noexcept;
};

///The SILs of this latest generation have been tallied,
///and are added to the graph here. The vertex descriptors
///are returned to work with
std::vector<sil_frequency_vertex_descriptor> add_sils(
  const std::map<sil,int>& m,
  const int t,
  sil_frequency_phylogeny& g
) noexcept;


///vds are collected per cohort. This function checks if indeed
///they have are from the same time
bool all_vds_have_same_time(
  const std::vector<sil_frequency_vertex_descriptor>& vds,
  const sil_frequency_phylogeny& g
) noexcept;

///These vds have been collected when adding new genotypes.
///The vertex descriptors should each point to a vertex with a unique SIL
bool all_vds_have_unique_sil(
  const std::vector<sil_frequency_vertex_descriptor>& vds,
  const sil_frequency_phylogeny& g
) noexcept;

///Connect the vertices of SILs that can create viable offspring together
void connect_species_within_cohort(
  const std::vector<sil_frequency_vertex_descriptor>& vds,
  const int max_genetic_distance,
  sil_frequency_phylogeny& g
) noexcept;

///Connect the vertices of SILs that can create viable offspring together
void connect_species_between_cohorts(
  const std::vector<sil_frequency_vertex_descriptor>& vds,
  const std::vector<sil_frequency_vertex_descriptor>& vds_prev,
  const int max_genetic_distance,
  sil_frequency_phylogeny& g
) noexcept;

///Count the total number of SILs these vds point to
int count_sils(
  const std::vector<sil_frequency_vertex_descriptor>& vds,
  const sil_frequency_phylogeny& g
) noexcept;

std::ostream& operator<<(std::ostream& os, const results& r) noexcept;

#endif // RESULTS_H
