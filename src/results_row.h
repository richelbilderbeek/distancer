#ifndef RESULTS_ROW_H
#define RESULTS_ROW_H

#include <iosfwd>
#include <string>

class results_row
{
public:
  results_row(
    const int n_individuals,
    const int t
  );
  static std::string get_header() noexcept { return "t, n"; }
private:
  int m_n_individuals;
  int m_t;

  friend std::ostream& operator<<(std::ostream& os, const results_row& r) noexcept;
};

std::ostream& operator<<(std::ostream& os, const results_row& r) noexcept;

#endif // RESULTS_ROW_H
