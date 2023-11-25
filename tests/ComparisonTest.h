
#ifndef _COMPARISONTEST_H
#define _COMPARISONTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <fraca7/distance.hpp>

class ComparisonTest : public CppUnit::TestFixture {
public:
  void testEquality() {
    fraca7::millimeters d1(20);
    fraca7::centimeters d2(2);

    CPPUNIT_ASSERT(d1 == d2);
  }

  void testInf() {
    fraca7::millimeters d1(2);
    fraca7::centimeters d2(1);

    CPPUNIT_ASSERT(d1 < d2);
    CPPUNIT_ASSERT(!(d2 < d1));
  }

  CPPUNIT_TEST_SUITE(ComparisonTest);
  CPPUNIT_TEST(testEquality);
  CPPUNIT_TEST(testInf);
  CPPUNIT_TEST_SUITE_END();
};

#endif
