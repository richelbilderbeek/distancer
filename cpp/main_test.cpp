#define BOOST_TEST_DYN_LINK // Defines a main function

#define BOOST_TEST_MODULE test_distancer_module
#include <boost/test/unit_test.hpp>

// /usr/include/boost/test/unit_test_suite_impl.hpp:255: error: undefined reference to `boost::unit_test::ut_detail::normalize_test_case_name(boost::unit_test::basic_cstring<char const>)'

// When compiling with g++-4.8, this will result in a segmentation fault
// *** Error in `/home/richel/GitHubs/distancer/build-distancer_test-Desktop-Debug/distancer_test': malloc(): memory corruption (fast): 0x0840a060 ***
// Press <RETURN> to close this window...
/*
//Located in /usr/include/boost/test/impl/unit_test_suite.ipp, approx line 222:

namespace boost {
namespace unit_test {
namespace ut_detail {

std::string normalize_test_case_name(const_string name)
{
  return name[0] == '&'
  ? std::string(name.begin() + 1, name.size() - 1)
  : std::string(name.begin(), name.size())
  ;
}

} //~namespace ut_detail
} //~namespace unit_test
} //~namespace boost
*/
