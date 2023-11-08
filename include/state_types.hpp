#pragma once

#include <iostream>

namespace tags
{
struct KIN_T {
};
struct DYN_T {
};
}  // namespace tags

template <typename T>
struct CarStateVec {
};

template <typename T>
struct InputVec {
};

template <>
struct CarStateVec<tags::KIN_T> {
  double x{.0f};
  double y{.0f};
  double yaw{.0f};
  double v{.0f};

  void log() const noexcept { std::cout << x << " " << y << " " << yaw << " " << v << std::endl; }
};

template <>
struct CarStateVec<tags::DYN_T> {
  double x{.0f};
  double y{.0f};
  double yaw{.0f};
  double vx{.0f};
  double vy{.0f};
  double r{.0f};  // dot_omega

  void log() const noexcept
  {
    std::cout << x << " " << y << " " << yaw << " " << vx << " " << vy << " " << r << std::endl;
  }
};

template <>
struct InputVec<tags::KIN_T> {
  double a;
  double steeringAngle;
};

template <>
struct InputVec<tags::DYN_T> {
  double throttle;
  double steeringAngle;
  double brakes;
};