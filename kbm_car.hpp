#pragma once

#include <iostream>

const double WheelBase = 1.5;

namespace kbm
{

struct CarStateVec {
  double x{0.0}, y{0.0}, yaw{0.0}, steeringAngle{0.0};
};

struct CarStateChangeVec {
  double a, steeringAngle;
};

class Car final
{
public:
  void influence(CarStateChangeVec &&changeVec) {}

  void printState() const noexcept
  {
    std::cout << d_state.x << " " << d_state.y << " " << d_state.yaw << " "
              << d_state.steeringAngle;
  }

private:
  CarStateVec d_state;
};
}  // namespace kbm