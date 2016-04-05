#include "distancer_sil_frequency_vertex.h"
#include <sstream>
#include <stdexcept>

sil_frequency_vertex::sil_frequency_vertex()
  : m_frequency{},
    m_sil{},
    m_time{0}
{

}


sil_frequency_vertex::sil_frequency_vertex(
  const int frequency,
  const sil& any_sil,
  const int time
)
  : m_frequency{frequency},
    m_sil{any_sil},
    m_time{time}
{
  if (m_frequency < 0)
  {
    std::stringstream msg;
    msg << __func__ << ": "
      << "frequency must be zero or positive, instead of "
      << m_frequency
    ;
    throw std::invalid_argument(msg.str());
  }
  if (m_time < 0)
  {
    std::stringstream msg;
    msg << __func__ << ": "
      << "time must be zero or positive, instead of "
      << m_time
    ;
    throw std::invalid_argument(msg.str());
  }
}
