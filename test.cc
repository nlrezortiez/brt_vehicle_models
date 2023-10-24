#ifdef DBM
#include "dbm_car.hpp"

#else
#include "kbm_car.hpp"

#endif

#include <iostream>
#include <fstream>

int main()
{
  kbm::Car car{};

  std::ifstream in{"input.txt"};

  int n;
  in >> n;

  for (int i = 0; i < n; ++i) {
    double a, stAngle;
    in >> a >> stAngle;
    car.influence({a, stAngle});
  }

  return EXIT_SUCCESS;
}