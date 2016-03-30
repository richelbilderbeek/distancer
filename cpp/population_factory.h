#ifndef POPULATION_FACTORY_H
#define POPULATION_FACTORY_H

#include "individual.h"

class population_factory
{
public:
  population_factory() {}
  using population = std::vector<individual>;
  population create_population_no_individuals() const noexcept;
  population create_population_one_individual() const noexcept;
  population create_population_two_individuals_one_species() const noexcept;
  population create_population_two_individuals_two_species() const noexcept;
  population create_population_three_individuals_two_species() const noexcept;
  population create_population_three_individuals_one_species_one_possible_species() const noexcept;
};

#endif // POPULATION_FACTORY_H
