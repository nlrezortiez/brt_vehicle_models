#include <vector>

#include "car_model.hpp"
#include "input_handler.hpp"

int main()
{
#ifdef DBM
  CarModel<tags::DYN_T> car{};
#else
  CarModel<tags::KIN_T> car{};
#endif

  std::vector<InputVec<decltype(car)::modelType>> inputChanges;
  getChanges(inputChanges);

  for (const auto &input : inputChanges) {
    car.nextState(input);
    // car.log();
  }

  return EXIT_SUCCESS;
}