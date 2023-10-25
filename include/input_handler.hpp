#pragma once

#include "state_types.hpp"

#include <vector>
#include <fstream>

template <typename CarModelType = tags::KIN_T>
void getChanges(std::vector<InputVec<CarModelType>> &changesVec)
{
  std::ifstream input{"../test_data/input.txt", std::ios_base::in};
  int n;
  input >> n;

  changesVec.reserve(n);

  for (int i = 0; i < n; ++i) {
    double acceleration;
    double steeringAngle;
    input >> acceleration >> steeringAngle;

    changesVec.push_back({acceleration, steeringAngle});
  }
}

template <>
void getChanges<tags::DYN_T>(std::vector<InputVec<tags::DYN_T>> &changes)
{
  std::ifstream input{"../test_data/input1.txt", std::ios_base::in};
  int n;
  input >> n;

  changes.reserve(n);

  for (int i = 0; i < n; ++i) {
    double throttle;
    double steeringAngle;
    double brakes;
    input >> throttle >> steeringAngle >> brakes;

    changes.push_back({throttle, steeringAngle, brakes});
  }
}