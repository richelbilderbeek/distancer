#include "population_factory.h"

population_factory::population population_factory::create_population_no_individuals() const noexcept
{
  return {};
}


population_factory::population population_factory::create_population_one_individual() const noexcept
{
  return population{
    individual(individual::pin_t(""),individual::sil_t(2, 0b00))
  };
}

population_factory::population population_factory::create_population_two_individuals_one_species() const noexcept
{
  return population{
    individual(individual::pin_t(""),individual::sil_t(2, 0b00)),
    individual(individual::pin_t(""),individual::sil_t(2, 0b01))
  };
}

population_factory::population population_factory::create_population_two_individuals_two_species() const noexcept
{
  return population{
    individual(individual::pin_t(""),individual::sil_t(2, 0b00)),
    individual(individual::pin_t(""),individual::sil_t(2, 0b11))
  };
}

population_factory::population population_factory::create_population_three_individuals_two_species() const noexcept
{
  return population{
    individual(individual::pin_t(""),individual::sil_t(2, 0b00)),
    individual(individual::pin_t(""),individual::sil_t(2, 0b00)),
    individual(individual::pin_t(""),individual::sil_t(2, 0b11))
  };
}

population_factory::population population_factory::create_population_three_individuals_one_species_one_possible_species() const noexcept
{
  return population{
    individual(individual::pin_t(""),individual::sil_t(2, 0b00)),
    individual(individual::pin_t(""),individual::sil_t(2, 0b01)),
    individual(individual::pin_t(""),individual::sil_t(2, 0b11))
  };
}
