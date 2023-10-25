#pragma once

#include "state_types.hpp"

#include <cmath>

template <typename CarModelType = tags::KIN_T>
class CarModel final
{
public:
  using modelType = CarModelType;

public:
  void influence(const InputVec<tags::KIN_T> &inputVec) noexcept
  {
    d_state.v += inputVec.a * d_dt;
    d_state.yaw += d_state.v * (std::tan(inputVec.steeringAngle) / d_carSpecs.L) * d_dt;

    d_state.x += d_state.v * std::cos(d_state.yaw) * d_dt;
    d_state.y += d_state.v * std::sin(d_state.yaw) * d_dt;
  }

  void influence(const InputVec<tags::DYN_T> &inputVec) noexcept
  {
    // force of traction motor applied to the rear wheel
    double F_drv = inputVec.throttle * d_carSpecs.C_m * inputVec.throttle;  // towards rear

    // rolling friction forces
    double F_rrr = d_carSpecs.C_rr * std::tanh(d_state.v_x);  // against rear
    double F_rrf = d_carSpecs.C_rr * std::tanh(d_state.v_x);  // against front

    // frontal aerodynamic drag force
    double F_drag = d_carSpecs.C_d * d_state.v_x * d_state.v_x;  // vehicle's MC

    // brake forces
    double F_bf = inputVec.brakes * d_carSpecs.C_bf * std::tanh(d_state.v_x);  // against frot
    double F_br = inputVec.brakes * d_carSpecs.C_br * std::tanh(d_state.v_x);  // against rear

    // adhession forces

    // double a_r{(F_drv - F_rrr - F_br) / d_carSpecs.m};
    // double a_f{(-F_rrf - F_bf) / d_carSpecs.m};

    // double F_ry = d_carSpecs.C_x * a_r;  //  * (\sum(forces_r) / m) // rear
    // double F_fy = d_carSpecs.C_x * a_f;  //  * (\sum(forces_f) / m) // front

    d_state.yaw = d_state.r;

    d_state.v_x = d_state.v_x * std::cos(d_state.yaw) - d_state.v_y * std::sin(d_state.yaw);
    d_state.v_y = d_state.v_y * std::cos(d_state.yaw) + d_state.v_x * std::sin(d_state.yaw);
  }

  void log() const noexcept { d_state.log(); }

private:
  struct CarSpecs {
    // Kinetic part

    // wheel base
    double L{1.5f};

    // Dynamic part

    // mass
    double m{300.0f};

    // inertia moment
    double l_z{134.0f};

    // distance from front and rear axes to MC, respectively
    double l_f{0.721f}, lr{0.823f};

    // max engine force to the rear wheel
    double C_m{3600.0f};

    // max rolling friction force
    double C_rr{200.0f};

    // coefficient of frontal aerodynamic drag
    double C_d{1.53f};

    // max braking force applied to the front and rear wheels, respectively
    double C_bf{5411.0f}, C_br{2650.0f};

    // coefficient for adhession calculations
    double C_x{20000.0f};
  };

private:
  CarStateVec<CarModelType> d_state{};
  CarSpecs d_carSpecs{};

  double d_dt{.5f};
};
