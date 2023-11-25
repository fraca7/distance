
#ifndef _CASTTEST_H
#define _CASTTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <fraca7/distance.hpp>

class CastTest : public CppUnit::TestFixture {
public:
  void testCastDown() {
    auto d = fraca7::distance_cast<fraca7::centimeters>(_20m);

    CPPUNIT_ASSERT(d.num() == 1);
    CPPUNIT_ASSERT(d.den() == 100);
    CPPUNIT_ASSERT(d.count() == 2000);
  }

  void testCastUp() {
    auto d = fraca7::distance_cast<fraca7::decameters>(_20m);

    CPPUNIT_ASSERT(d.num() == 10);
    CPPUNIT_ASSERT(d.den() == 1);
    CPPUNIT_ASSERT(d.count() == 2);
  }

  void testCastMult() {
    fraca7::distance<intmax_t, std::ratio<1, 15>> d1(4);
    auto d = fraca7::distance_cast<fraca7::distance<intmax_t, std::ratio<1, 8>>>(d1);

    CPPUNIT_ASSERT(d.num() == 1);
    CPPUNIT_ASSERT(d.den() == 8);
    CPPUNIT_ASSERT(d.count() == 4 * 8 / 15);
  }

  void testConstruction() {
    fraca7::millimeters d(fraca7::centimeters(2));

    CPPUNIT_ASSERT(d.num() == 1);
    CPPUNIT_ASSERT(d.den() == 1000);
    CPPUNIT_ASSERT(d.count() == 20);
  }

  void testCastToFloat() {
    auto d = fraca7::distance_cast<fraca7::meters::as<float>>(fraca7::centimeters(50));

    CPPUNIT_ASSERT(d.num() == 1);
    CPPUNIT_ASSERT(d.den() == 1);
    CPPUNIT_ASSERT(d.count() == 0.5f);
  }

  CPPUNIT_TEST_SUITE(CastTest);
  CPPUNIT_TEST(testCastDown);
  CPPUNIT_TEST(testCastUp);
  CPPUNIT_TEST(testCastMult);
  CPPUNIT_TEST(testConstruction);
  CPPUNIT_TEST(testCastToFloat);
  CPPUNIT_TEST_SUITE_END();

private:
  fraca7::meters _20m{20};
};

#endif
