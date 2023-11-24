#pragma once

#include "state_types.hpp"

#include <vector>
#include <fstream>

int n_changes = 0;

template <typename CarModelType>
void getChanges(std::vector<InputVec<CarModelType>> &);

template <>
void getChanges(std::vector<InputVec<tags::KIN_T>> &changesVec)
{
  std::ifstream input{"../test_data/input.txt", std::ios_base::in};
  input >> n_changes;

  changesVec.reserve(n_changes);

  for (int i = 0; i < n_changes; ++i) {
    double acceleration;
    double steeringAngle;
    input >> acceleration >> steeringAngle;

    changesVec.push_back({acceleration, steeringAngle});
  }
}

template <>
void getChanges<tags::DYN_T>(std::vector<InputVec<tags::DYN_T>> &changesVec)
{
  std::ifstream input{"../test_data/input1.txt", std::ios_base::in};
  input >> n_changes;

  changesVec.reserve(n_changes);

  for (int i = 0; i < n_changes; ++i) {
    double throttle;
    double steeringAngle;
    double brakes;
    input >> throttle >> steeringAngle >> brakes;

    changesVec.push_back({throttle, steeringAngle, brakes});
  }
}