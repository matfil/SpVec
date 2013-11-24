#include "SpVec.hpp"
#define BOOST_TEST_MODULE SPVECTEST
#include <boost/test/included/unit_test.hpp>



BOOST_AUTO_TEST_CASE( correctness )
{

  SpVec<int> a(5);


  BOOST_CHECK_EQUAL(5, 5);
  BOOST_CHECK_EQUAL(6, 5);
}

