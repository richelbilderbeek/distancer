#ifndef DNA_H
#define DNA_H

#include <string>

class dna
{
public:
  dna(const std::string& sequence);

  const std::string& get_sequence() const noexcept { return m_sequence; }

  std::string::size_type size() const noexcept { return m_sequence.size(); }

  const char& operator[](const size_t i) const noexcept { return m_sequence[i]; }
        char& operator[](const size_t i)       noexcept { return m_sequence[i]; }

private:
  std::string m_sequence;
};

bool operator==(const dna& lhs, const dna& rhs) noexcept;

#endif // DNA_H
