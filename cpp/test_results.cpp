#include "results.h"
#include <boost/test/unit_test.hpp>
#include "population_factory.h"

BOOST_AUTO_TEST_CASE(test_results_detect_species_initiation)
{
  results r;
  const int max_genetic_distance{1};

  std::vector<individual> p{
    individual(individual::pin_t(""),individual::sil_t(2, 0b00)),
    individual(individual::pin_t(""),individual::sil_t(2, 0b01)),
    individual(individual::pin_t(""),individual::sil_t(2, 0b01))
  }

  r.add_measurement(0, p, max_genetic_distance);

  std::vector<individual> p{
    individual(individual::pin_t(""),individual::sil_t(2, 0b00)),
    individual(individual::pin_t(""),individual::sil_t(2, 0b01)),
    individual(individual::pin_t(""),individual::sil_t(2, 0b11))
  }

  r.add_measurement(1, p, max_genetic_distance);

  r.get_incipient
}


