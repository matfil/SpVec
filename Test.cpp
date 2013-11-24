#include "SpVec.hpp"
#define BOOST_TEST_MODULE SPVECTEST
#include <boost/test/included/unit_test.hpp>

#include <iostream>
using namespace std;

BOOST_AUTO_TEST_CASE( correctness )
{

  SpVec<int> a(5);
  cout << "nonzero:" << a.nonzero() << "size" << a.size() << endl;
  a[2] = 3; 
  cout << "nonzero:" << a.nonzero() << endl;
  BOOST_CHECK_EQUAL(a.size(), 5);
  BOOST_CHECK_EQUAL(a.nonzero(), 1);
}

