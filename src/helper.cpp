#include "helper.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <stdexcept>

///Counts the number of bits that are different
int count_different_bits(
  const boost::dynamic_bitset<>& a,
  const boost::dynamic_bitset<>& b
) noexcept
{
  return (a ^ b).count();
}

boost::dynamic_bitset<> create_offspring(
  const boost::dynamic_bitset<>& p,
  const boost::dynamic_bitset<>& q,
  const boost::dynamic_bitset<>& inherit_from_p
)
{
  assert(p.size() == q.size());
  assert(p.size() == inherit_from_p.size());
  return (inherit_from_p & p) | (~inherit_from_p & q);
}

dna create_offspring(
  const dna& p,
  const dna& q,
  const boost::dynamic_bitset<>& inherit_from_p
)
{
  assert(p.size() == q.size());
  assert(p.size() == inherit_from_p.size());
  const auto sz = p.size();
  dna r{q};
  for (size_t i = 0; i!=sz; ++i)
  {
    if ( (1 << (sz - 1 - i)) //Use little-endian
      & inherit_from_p.to_ulong() )
    {
      r[i] = p[i];
    }
  }
  return r;
}


#ifdef REALLY_USE_BPP
bpp::BasicSequence create_offspring(
  const bpp::BasicSequence& p,
  const bpp::BasicSequence& q,
  const boost::dynamic_bitset<>& inherit_from_p
)
{
  assert(p.size() == q.size());
  assert(p.size() == inherit_from_p.size());
  const auto sz = p.size();
  bpp::BasicSequence r{q};
  for (size_t i = 0; i!=sz; ++i)
  {
    if ( (1 << (sz - 1 - i)) //Use little-endian
      & inherit_from_p.to_ulong() )
    {
      r.setElement(i, p.getChar(i));
    }
  }
  return r;
}
#endif //REALLY_USE_BPP

std::vector<int> create_tally(const std::vector<int>& v) noexcept
{
  std::map<int, int> m;
  for (const auto i: v)
  {
    const auto iter = m.find(i);
    if (iter == std::end(m))
    {
      m.insert(std::make_pair(i, 1));
    }
    else { ++m[i]; }
  }

  std::vector<int> t;
  t.reserve(m.size());
  for (const auto p: m) {
    t.push_back(p.second);
  }
  return t;
}

std::vector<std::string> file_to_vector(const std::string& filename)
{
  if (!is_regular_file(filename)) {
    std::stringstream msg;
    msg << __func__ << ": filename '"
      << filename << "' not found"
    ;
    throw std::invalid_argument(msg.str());
  }
  std::vector<std::string> v;
  std::ifstream in(filename.c_str());
  for (int i=0; !in.eof(); ++i)
  {
    std::string s;
    std::getline(in,s);
    v.push_back(s);
  }
  return v;
}

bool is_regular_file(const std::string& filename) noexcept
{
  std::fstream f;
  f.open(filename.c_str(),std::ios::in);
  return f.is_open();
}

