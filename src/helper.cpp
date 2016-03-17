#include "helper.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

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

