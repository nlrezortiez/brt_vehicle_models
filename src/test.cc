#include "car_model.hpp"

#include <fstream>
#include <vector>

template <typename CarModelType>
[[nodiscard]] std::size_t getChanges(std::vector<CarStateChangeVec<CarModelType>> &);

template <>
[[nodiscard]] std::size_t getChanges<tags::KIN_T>(
  std::vector<CarStateChangeVec<tags::KIN_T>> &changesVec)
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
  return n;
}

template <>
[[nodiscard]] std::size_t getChanges<tags::DYN_T>(
  std::vector<CarStateChangeVec<tags::DYN_T>> &changes)
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
  return n;
}

int main()
{
#ifdef DBM
  CarModel<tags::DYN_T> car{};
  std::vector<CarStateChangeVec<tags::DYN_T>> inputChanges;
#else
  CarModel<tags::KIN_T> car{};
  std::vector<CarStateChangeVec<tags::KIN_T>> inputChanges;
#endif

  auto n = getChanges(inputChanges);
  for (int i = 0; i < n; ++i) {
    car.influence(inputChanges[i]);
    car.log();
  }

  return EXIT_SUCCESS;
}