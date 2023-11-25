
#ifndef _ARITHMETICTEST_H
#define _ARITHMETICTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <fraca7/distance.hpp>

class ArithmeticTest : public CppUnit::TestFixture {
public:
  void testUnaryPlus() {
    fraca7::centimeters d(3);
    auto v = +d;

    CPPUNIT_ASSERT(v.num() == 1);
    CPPUNIT_ASSERT(v.den() == 100);
    CPPUNIT_ASSERT(v.count() == 3);
  }

  void testUnaryMinus() {
    fraca7::centimeters d(3);
    auto v = -d;

    CPPUNIT_ASSERT(v.num() == 1);
    CPPUNIT_ASSERT(v.den() == 100);
    CPPUNIT_ASSERT(v.count() == -3);
  }

  void testPrefixIncrement() {
    fraca7::centimeters d(3);
    auto val = ++d;

    CPPUNIT_ASSERT(val.num() == 1);
    CPPUNIT_ASSERT(val.den() == 100);
    CPPUNIT_ASSERT(val.count() == 4);
    CPPUNIT_ASSERT(d.count() == 4);
  }

  void testSuffixIncrement() {
    fraca7::centimeters d(3);
    auto val = d++;

    CPPUNIT_ASSERT(val.num() == 1);
    CPPUNIT_ASSERT(val.den() == 100);
    CPPUNIT_ASSERT(val.count() == 3);
    CPPUNIT_ASSERT(d.count() == 4);
  }

  void testPrefixDecrement() {
    fraca7::centimeters d(3);
    auto val = --d;

    CPPUNIT_ASSERT(val.num() == 1);
    CPPUNIT_ASSERT(val.den() == 100);
    CPPUNIT_ASSERT(val.count() == 2);
    CPPUNIT_ASSERT(d.count() == 2);
  }

  void testSuffixDecrement() {
    fraca7::centimeters d(3);
    auto val = d--;

    CPPUNIT_ASSERT(val.num() == 1);
    CPPUNIT_ASSERT(val.den() == 100);
    CPPUNIT_ASSERT(val.count() == 3);
    CPPUNIT_ASSERT(d.count() == 2);
  }

  void testInplaceAdd() {
    fraca7::centimeters d(3);
    auto val = d += fraca7::decimeters(2);

    CPPUNIT_ASSERT(val.num() == 1);
    CPPUNIT_ASSERT(val.den() == 100);
    CPPUNIT_ASSERT(val.count() == 23);
    CPPUNIT_ASSERT(d.count() == 23);
  }

  void testInplaceSub() {
    fraca7::centimeters d(30);
    auto val = d -= fraca7::decimeters(1);

    CPPUNIT_ASSERT(val.num() == 1);
    CPPUNIT_ASSERT(val.den() == 100);
    CPPUNIT_ASSERT(val.count() == 20);
    CPPUNIT_ASSERT(d.count() == 20);
  }

  void testAdd() {
    fraca7::centimeters d1(5);
    fraca7::meters d2(1);
    auto d = d1 + d2;

    CPPUNIT_ASSERT(d.num() == 1);
    CPPUNIT_ASSERT(d.den() == 100);
    CPPUNIT_ASSERT(d.count() == 105);
  }

  void testSub() {
    fraca7::meters d1(1);
    fraca7::centimeters d2(8);
    auto d = d1 - d2;

    CPPUNIT_ASSERT(d.num() == 1);
    CPPUNIT_ASSERT(d.den() == 100);
    CPPUNIT_ASSERT(d.count() == 92);
  }

  void testScalarInplaceMultiply() {
    fraca7::centimeters d(3);
    auto val = d *= 5;

    CPPUNIT_ASSERT(val.num() == 1);
    CPPUNIT_ASSERT(val.den() == 100);
    CPPUNIT_ASSERT(val.count() == 15);
    CPPUNIT_ASSERT(d.count() == 15);
  }

  void testScalarMultiplyRight() {
    auto d = fraca7::millimeters(2) * 3;

    CPPUNIT_ASSERT(d.num() == 1);
    CPPUNIT_ASSERT(d.den() == 1000);
    CPPUNIT_ASSERT(d.count() == 6);
  }

  void testScalarMultiplyLeft() {
    auto d = 3 * fraca7::millimeters(2);

    CPPUNIT_ASSERT(d.num() == 1);
    CPPUNIT_ASSERT(d.den() == 1000);
    CPPUNIT_ASSERT(d.count() == 6);
  }

  void testScalarInplaceDivide() {
    fraca7::centimeters d(16);
    auto val = d /= 5;

    CPPUNIT_ASSERT(val.num() == 1);
    CPPUNIT_ASSERT(val.den() == 100);
    CPPUNIT_ASSERT(val.count() == 3);
    CPPUNIT_ASSERT(d.count() == 3);
  }

  void testScalarDivide() {
    fraca7::centimeters d(17);
    auto val = d / 8;

    CPPUNIT_ASSERT(val.num() == 1);
    CPPUNIT_ASSERT(val.den() == 100);
    CPPUNIT_ASSERT(val.count() == 2);
  }

  void testFloatDivide() {
    fraca7::centimeters d(1);
    auto val = d / 2.f;

    CPPUNIT_ASSERT(val.num() == 1);
    CPPUNIT_ASSERT(val.den() == 100);
    CPPUNIT_ASSERT(val.count() == 0.5f);
  }

  void testDistanceDivide() {
    fraca7::centimeters d1(6);
    fraca7::millimeters d2(2);
    auto val = d1 / d2;

    CPPUNIT_ASSERT(val == 30);
  }

  void testScalarInplaceModulo() {
    fraca7::centimeters d(13);
    auto val = d %= 5;

    CPPUNIT_ASSERT(val.num() == 1);
    CPPUNIT_ASSERT(val.den() == 100);
    CPPUNIT_ASSERT(val.count() == 3);
    CPPUNIT_ASSERT(d.count() == 3);
  }

  void testDistanceInplaceModulo() {
    fraca7::millimeters d(130);
    auto val = d %= fraca7::centimeters(5);

    CPPUNIT_ASSERT(val.num() == 1);
    CPPUNIT_ASSERT(val.den() == 1000);
    CPPUNIT_ASSERT(val.count() == 30);
    CPPUNIT_ASSERT(d.count() == 30);
  }

  void testScalarModulo() {
    fraca7::centimeters d{13};
    auto val = d % 5;

    CPPUNIT_ASSERT(val.num() == 1);
    CPPUNIT_ASSERT(val.den() == 100);
    CPPUNIT_ASSERT(val.count() == 3);
  }

  void testDistanceModulo() {
    fraca7::millimeters d(130);
    auto val = d % fraca7::centimeters(5);

    CPPUNIT_ASSERT(val.num() == 1);
    CPPUNIT_ASSERT(val.den() == 1000);
    CPPUNIT_ASSERT(val.count() == 30);
  }

  CPPUNIT_TEST_SUITE(ArithmeticTest);
  CPPUNIT_TEST(testUnaryPlus);
  CPPUNIT_TEST(testUnaryMinus);
  CPPUNIT_TEST(testPrefixIncrement);
  CPPUNIT_TEST(testSuffixIncrement); 
  CPPUNIT_TEST(testPrefixDecrement);
  CPPUNIT_TEST(testSuffixDecrement);
  CPPUNIT_TEST(testInplaceAdd);
  CPPUNIT_TEST(testInplaceSub); 
  CPPUNIT_TEST(testAdd);
  CPPUNIT_TEST(testSub);
  CPPUNIT_TEST(testScalarInplaceMultiply);
  CPPUNIT_TEST(testScalarMultiplyRight);
  CPPUNIT_TEST(testScalarMultiplyLeft);
  CPPUNIT_TEST(testScalarInplaceDivide);
  CPPUNIT_TEST(testScalarDivide);
  CPPUNIT_TEST(testFloatDivide);
  CPPUNIT_TEST(testDistanceDivide);
  CPPUNIT_TEST(testScalarInplaceModulo);
  CPPUNIT_TEST(testDistanceInplaceModulo);
  CPPUNIT_TEST(testScalarModulo);
  CPPUNIT_TEST(testDistanceModulo);
  CPPUNIT_TEST_SUITE_END();
};

#endif
