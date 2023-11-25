
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(fraca7_distance_unittests)

include(FindPkgConfig)
pkg_search_module(CPPUNIT REQUIRED cppunit)
include_directories(${CPPUNIT_INCLUDE_DIRS})
link_directories(${CPPUNIT_LIBRARY_DIRS})

add_executable(unittests
  tests/main.cpp
  tests/CastTest.h
  tests/CastTest.cpp
  tests/ArithmeticTest.h
  tests/ArithmeticTest.cpp
  tests/ComparisonTest.h
  tests/ComparisonTest.cpp
  )

include_directories(${PROJECT_SOURCE_DIR}/include)

target_link_libraries(unittests ${CPPUNIT_LIBRARIES})
