#ifndef ABUNDANCES_H
#define ABUNDANCES_H

#include <iosfwd>
#include <string>
#include <vector>

class abundances
{
public:
  abundances(
    const std::vector<int>& individuals_per_species,
    const int t
  );
  int get_n_species() const noexcept { return static_cast<int>(m_individuals_per_species.size()); }
  const std::vector<int>& get_individuals_per_species() const noexcept { return m_individuals_per_species; }
private:
  std::vector<int> m_individuals_per_species;
  int m_t;

  friend std::ostream& operator<<(std::ostream& os, const abundances& r) noexcept;
};

std::ostream& operator<<(std::ostream& os, const abundances& r) noexcept;

#endif // ABUNDANCES_H
