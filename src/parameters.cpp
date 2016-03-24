#include "parameters.h"
#include <sstream>
#include <stdexcept>

parameters::parameters(
  const int max_genetic_distance,
  const double mutation_rate,
  const int n_generations,
  const std::size_t n_pin_loci,
  const std::size_t n_sil_loci,
  const int population_size,
  const std::string& results_filename,
  const int rng_seed,
  const int sampling_interval
)
  : m_max_genetic_distance{max_genetic_distance},
    m_mutation_rate{mutation_rate},
    m_n_generations{n_generations},
    m_n_pin_loci{n_pin_loci},
    m_n_sil_loci{n_sil_loci},
    m_population_size{population_size},
    m_results_filename{results_filename},
    m_rng_seed{rng_seed},
    m_sampling_interval{sampling_interval}
{
  if (m_max_genetic_distance < 0)
  {
    std::stringstream msg;
    msg << __func__ << ": "
      << "max_genetic_distance must be >= 1, "
      << "supplied value was " << m_max_genetic_distance
    ;
    throw std::invalid_argument(msg.str());
  }
  if (m_mutation_rate < 0.0)
  {
    std::stringstream msg;
    msg << __func__ << ": "
      << "mutation rate must be >= 0.0, "
      << "supplied value was " << m_mutation_rate
    ;
    throw std::invalid_argument(msg.str());
  }
  if (m_mutation_rate > 1.0)
  {
    std::stringstream msg;
    msg << __func__ << ": "
      << "mutation rate must be <= 1.0, "
      << "supplied value was " << m_mutation_rate
    ;
    throw std::invalid_argument(msg.str());
  }
  if (m_n_generations < 0)
  {
    std::stringstream msg;
    msg << __func__ << ": "
      << "n_generations must be >= 0, "
      << "supplied value was " << m_n_generations
    ;
    throw std::invalid_argument(msg.str());
  }
  if (m_population_size < 0)
  {
    std::stringstream msg;
    msg << __func__ << ": "
      << "population_size must be >= 0, "
      << "supplied value was " << m_population_size
    ;
    throw std::invalid_argument(msg.str());
  }
  if (results_filename.empty())
  {
    std::stringstream msg;
    msg << __func__ << ": "
      << "results_filename must be non-empty"
    ;
    throw std::invalid_argument(msg.str());
  }
  //Allow a population of zero generations
  if (m_n_generations > 0 && m_sampling_interval < 1)
  {
    std::stringstream msg;
    msg << __func__ << ": "
      << "sampling_interval must be >= 1, "
      << "supplied value was " << m_sampling_interval
    ;
    throw std::invalid_argument(msg.str());
  }
  //Allow a population of zero generations
  if (m_n_generations > 0 && m_n_generations < m_sampling_interval)
  {
    std::stringstream msg;
    msg << __func__ << ": "
      << "sampling_interval must be >= n_generations "
      << "(otherwise only a measurement would be taken at the start), "
      << "sampling_interval: " << m_sampling_interval
      << "n_generations: " << m_n_generations
    ;
    throw std::invalid_argument(msg.str());
  }
}
