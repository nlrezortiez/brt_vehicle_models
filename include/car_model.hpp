#pragma once

#include "state_types.hpp"

#include <iostream>
#include <cmath>

template <typename CarModelType = tags::KIN_T>
class CarModel final
{
public:
  using modelType = CarModelType;

public:
  void influence(const CarStateChangeVec<tags::KIN_T> &changeVec) noexcept
  {
    d_state.v += changeVec.a * d_dt;
    d_state.x += d_state.v * std::cos(d_state.yaw) * d_dt;
    d_state.y += d_state.v * std::sin(d_state.yaw) * d_dt;
    d_state.yaw += d_state.v * (std::tan(changeVec.steeringAngle) / d_L) * d_dt;
  }

  void influence(const CarStateChangeVec<tags::DYN_T> &changeVec) noexcept
  {
    std::cout << "dynamic version" << std::endl;
  }

  void log() const noexcept { d_state.log(); }

private:
  CarStateVec<CarModelType> d_state{};
  double d_dt{.5f};
  double d_L{1.5f};  // wheel base
};
