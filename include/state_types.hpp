#pragma once

#include <iostream>

namespace tags
{
struct KIN_T {
};
struct DYN_T {
};
}  // namespace tags

template <typename CarModelType = tags::KIN_T>
struct CarStateVec {
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
  double v_x{.0f};
  double v_y{.0f};
  double r{.0f};  // omega

  void log() const noexcept
  {
    std::cout << x << " " << y << " " << yaw << " " << v_x << " " << v_y << " " << r << std::endl;
  }
};

template <typename CarModelType = tags::KIN_T>
struct InputVec {
  double a;
  double steeringAngle;
};

template <>
struct InputVec<tags::DYN_T> {
  double throttle;
  double steeringAngle;
  double brakes;
};