#include "../../../matrix.hpp"
#include <iostream>

void printM (const Matrix<float> M) {
  int rows = M.rows();
  int cols = M.cols();
  std::cout << std::endl;
  for (int i = 1; i <= rows; i++) {
    for (int j = 1; j <= cols; j++) {
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

  printM(B);
  B += B;
  printM(B);

  return 0;
}
