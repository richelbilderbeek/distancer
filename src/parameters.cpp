#include "parameters.h"
#include <sstream>
#include <stdexcept>

parameters::parameters(
  const int max_genetic_distance,
  const double mutation_rate,
  const int n_generations,
  const std::size_t n_loci,
  const int population_size,
  const int rng_seed
)
  : m_max_genetic_distance{max_genetic_distance},
    m_mutation_rate{mutation_rate},
    m_n_generations{n_generations},
    m_n_loci{n_loci},
    m_population_size{population_size},
    m_rng_seed{rng_seed}
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
}
