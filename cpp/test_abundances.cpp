#include "measurement.h"
#include <fstream>
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "helper.h"

// Boost.Test does not play well with -Weffc++
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

BOOST_AUTO_TEST_CASE(test_abundances)
{
  BOOST_CHECK_THROW(measurement( {}, -1), std::invalid_argument);
  BOOST_CHECK_THROW(measurement( { -1 }, 0), std::invalid_argument);
  const measurement a( { 1 }, 0);
  std::stringstream s;
  s << a;
  BOOST_CHECK(!s.str().empty());
}

#pragma GCC diagnostic pop


