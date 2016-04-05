#include "distancer_results_vertex.h"
#include <sstream>
#include <stdexcept>

results_vertex::results_vertex(
  const int frequency,
  const dna& any_pin,
  const sil& any_sil

)
  : m_frequency{frequency},
    m_pin{any_pin},
    m_sil{any_sil}
{
  if (m_frequency < 0)
  {
    std::stringstream msg;
    msg << __func__ << ": "
      << "frequency must be zero or positive, instead of "
      << frequency
    ;
    throw std::invalid_argument(msg.str());
  }
}
