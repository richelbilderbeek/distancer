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

std::string get_sil_frequencies_str(const sil_frequency_vertex& v) noexcept
{

  const auto fs = v.get_sil_frequencies();
  std::stringstream s;
  std::transform(std::begin(fs), std::end(fs),
    std::ostream_iterator<std::string>(s, ","),
    [](const std::pair<sil,int>& p)
    {
      std::stringstream t;
      t << "(" << p.first << ", " << p.second << ")";
      return t.str();
    }
  );
  std::string t{s.str()};
  if (!t.empty()) t.pop_back();
  return t;
}

void move_sil_frequencies(sil_frequency_vertex& from, sil_frequency_vertex& to)
{
  if (from.get_time() != to.get_time())
  {
    std::stringstream msg;
    msg << __func__ << ": "
      << "SIL frequencies may only be summed from the same generation"
    ;
    throw std::invalid_argument(msg.str());
  }
  const auto sizes_before = from.m_sil_frequencies.size() + to.m_sil_frequencies.size();

  //Create a copy of 'to' its SIL frequencies, to have the basic guarantee
  auto fs = to.get_sil_frequencies();
  std::copy(
    std::begin(from.m_sil_frequencies), std::end(from.m_sil_frequencies),
    std::inserter(fs, std::end(fs))
  );


  //Do we have a go to modify our vertices?
  const auto sizes_after = fs.size(); //fs -> to, nothing -> from
  if (sizes_before != sizes_after)
  {
    std::stringstream msg;
    msg << __func__ << ": "
      << "duplicate SIL frequency, a simple copy does not suffice here. "
      << "time: " << from.get_time()
      << ", genotypes 'from': " << get_sil_frequencies_str(from)
      << ", genotypes 'to': " << get_sil_frequencies_str(to)
    ;
    throw std::invalid_argument(msg.str());
  }
  to.m_sil_frequencies = fs;
  from.m_sil_frequencies.clear();
}
