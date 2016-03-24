#include "dna.h"
#include <sstream>

dna::dna(const std::string& sequence)
  : m_sequence{sequence}
{
  //const std::set<char> valid = { 'a','c','g','t' };
  for (const auto& c: sequence)
  {
    if (c != 'A' && c != 'C' && c != 'G' && c != 'T')
    {
      std::stringstream msg;
      msg << __func__ << ": invalid nucleotide '"
        << c << "' supplied with sequences '"
        << sequence << "'";
      throw std::invalid_argument(msg.str());
    }
  }
}


bool operator==(const dna& lhs, const dna& rhs) noexcept
{
  return lhs.get_sequence() == rhs.get_sequence();
}
