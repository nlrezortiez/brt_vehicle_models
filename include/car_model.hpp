#pragma once

#include <cmath>

#include "state_types.hpp"

template <typename CarModelType = tags::KIN_T>
class CarModel final
{
public:
  using modelType = CarModelType;

public:
  void nextState(const InputVec<tags::KIN_T> &inputVec) noexcept
  {
    auto prevState = d_state;
    d_state.v += inputVec.a * d_dt;
    d_state.x += prevState.v * std::cos(prevState.yaw) * d_dt;
    d_state.y += prevState.v * std::sin(prevState.yaw) * d_dt;
    d_state.yaw += prevState.v * (std::tan(inputVec.steeringAngle) / d_carSpecs.L) * d_dt;
  }

  void nextState(const InputVec<tags::DYN_T> &inputVec) noexcept
  {
    const double vx = d_state.vx;
    const double vy = d_state.vy;
    const double yaw = d_state.yaw;
    const double r = d_state.r;

    const double dDelta = inputVec.steeringAngle;
    const double throttle = inputVec.throttle;
    const double brakes = inputVec.brakes;

    double F_drv = throttle * throttle * d_carSpecs.C_m;

    double F_rrr = d_carSpecs.C_rr * std::tanh(d_state.vx);
    double F_rrf = d_carSpecs.C_rr * std::tanh(d_state.vx);

    double F_drag = d_carSpecs.C_d * vx * vx;

    double F_bf = brakes * d_carSpecs.C_bf * std::tanh(vx);
    double F_br = brakes * d_carSpecs.C_br * std::tanh(vx);

    double alpha_r = std::atan2(vy - d_carSpecs.l_r * r, vx);
    double alpha_f = std::atan2(vy + d_carSpecs.l_f * r, vx) - dDelta;

    double F_ry = d_carSpecs.C_x * alpha_r;
    double F_fy = d_carSpecs.C_x * alpha_f;

    d_state.x += d_dt * (vx * std::cos(yaw) - vy * std::sin(yaw));
    d_state.y += d_dt * (vy * std::cos(yaw) + vx * std::sin(yaw));
    d_state.yaw += d_dt * r;

    d_state.vx += d_dt * (1 / d_carSpecs.m *
                          (F_drv - F_drag - std::cos(dDelta) * (F_rrf + F_bf) - F_rrr - F_br -
                           F_fy * std::sin(dDelta)));

    d_state.vy += d_dt * (1 / d_carSpecs.m *
                          (-std::sin(dDelta) * (F_rrf + F_bf) + F_ry + F_fy * std::cos(dDelta)));

    d_state.r +=
      d_dt * (1 / d_carSpecs.I_z *
              (-F_ry * d_carSpecs.l_r +
               (F_fy * std::cos(dDelta) - (F_rrf + F_bf) * std::sin(dDelta)) * d_carSpecs.l_f));
  }

  void log() const noexcept { d_state.log(); }

private:
  struct CarSpecs {
    double L{1.5f};
    double m{300.0f};
    double I_z{134.0f};
    double l_f{0.721f}, l_r{0.823f};
    double C_m{3600.0f};
    double C_rr{200.0f};
    double C_d{1.53f};
    double C_bf{5411.0f}, C_br{2650.0f};
    double C_x{20000.0f};
  };

private:
  CarStateVec<CarModelType> d_state{};
  CarSpecs d_carSpecs{};

  double d_dt{.5f};
};
