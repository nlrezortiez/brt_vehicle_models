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

  int inputIdx = 1;

  for (double i = 0.0; i < car.d_dt * n_changes; i += 0.001) {
    if (std::abs(i - inputIdx * car.d_dt) <= 1e-6) {
      ++inputIdx;
      std::cout << "t=" << i << ": ";
      car.log();
    }

    car.nextState(inputChanges[inputIdx - 1]);
  }

  return EXIT_SUCCESS;
}