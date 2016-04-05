#include "distancer_sil_frequency_vertex.h"
#include <sstream>
#include <stdexcept>

sil_frequency_vertex::sil_frequency_vertex()
  : m_sil_frequencies{},
    m_time{}
{

}


sil_frequency_vertex::sil_frequency_vertex(
  const std::map<sil,int>& sil_frequencies,
  const int time
)
  : m_sil_frequencies{sil_frequencies},
    m_time{time}
{
  for (const auto p: m_sil_frequencies)
  {
    if (p.second < 0)
    {
      std::stringstream msg;
      msg << __func__ << ": "
        << "frequency must be zero or positive, instead of "
        << p.second
      ;
      throw std::invalid_argument(msg.str());
    }
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
