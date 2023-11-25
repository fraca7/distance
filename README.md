
# Type-safe distance library

Changelog

  * v1.0 - First release

## Overview

This library provides a *distance* template class that is loosely modeled after *std::chrono::duration*. The main difference here is that there is no analog to *std::chrono::clock* to provide a default granularity so you have to choose an explicit precision when declaring your variables.

You can specialize this class for the underlying storage type; most predefined specializations (*centimeters*, *meters*, etc) use a 64-bit signed integer.

There are specializations for the following units:

  * SI
    * angstrom
    * nanometers
    * micrometers (alias: microns)
    * millimeters
    * centimeters
    * decimeters
    * meters
    * decameters
    * hectometers
    * kilometers
  * MURICA
    * twips
    * thous
    * barleycorns
    * inches
    * hands
    * feet
    * yards
    * chains
    * furlongs
    * miles
    * leagues
  * Misc
    * cubics
    * attoparsecs
    * beard_seconds
    * light_seconds

## Installation

Copy include/fraca7 somewhere in your include path (there's a single *distance.hpp* file in there)

## Example usage

```

#include <iostream>
#include <fraca7/distance.hpp>

int main(int, char*[]) {
  fraca7::centimeters d(25);

  auto i = fraca7::distance_cast<fraca7::inches>(d);
  auto b = fraca7::distance_cast<fraca7::barleycorns>(d - i);

  std::cout << "25cm are " << i.count() << " inches and " << b.count() << " barleycorns" << std::endl;

  return 0;
}

```
