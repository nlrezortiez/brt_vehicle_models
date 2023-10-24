#pragma once

#include <iostream>

namespace tags
{
struct KIN_T {
};
struct DYN_T {
};
}  // namespace tags

template <typename CarModelType>
struct CarStateVec {
};

template <typename CarModelType>
struct CarStateChangeVec {
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
  double v_x{.0f};
  double v_y{.0f};
  double r{.0f};

  void log() const noexcept
  {
    std::cout << x << " " << y << " " << yaw << " " << v_x << " " << v_y << " " << r << std::endl;
  }
};

template <>
struct CarStateChangeVec<tags::KIN_T> {
  double a;
  double steeringAngle;
};

template <>
struct CarStateChangeVec<tags::DYN_T> {
  double throttle;
  double steeringAngle;
  double brakes;
};