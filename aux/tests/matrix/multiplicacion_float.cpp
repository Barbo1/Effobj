#include <iostream>

#include "../../../matrix.hpp"

void printm (Matrix<float> M) {
  std::cout << std::endl;
  for (uint64_t i = 1; i <= M.rows(); i++) {
    for (uint64_t j = 1; j <= M.cols(); j++) {
      std::cout << M(i, j) << " ";
    }
    std::cout << std::endl;
  }
}

int main () {
  Matrix<float> A = Matrix<float> (3, 4, new float[12]{
    0.25f, 0.5f, 0.f, 0.25f,
    0.f, 1.f, 0.f, 0.f,
    0.5f, 0.f, 0.5f, 0.f 
  }, true);

  Matrix<float> B = Matrix<float> (4, 4, new float [16] {
    3, 10, 12, 18,
    12, 1, 4, 9,
    9, 10, 12, 2,
    3, 12, 4, 10
  }, true);

  printm(A * B);

  return 0;
}
