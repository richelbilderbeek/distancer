#include "distancer_sil_frequency_vertex.h"
#include <sstream>
#include <stdexcept>

sil_frequency_vertex::sil_frequency_vertex(
  const int frequency,
  const sil& any_sil
)
  : m_frequency{frequency},
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
