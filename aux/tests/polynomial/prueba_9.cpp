#include "../../../polynomial.hpp"
#include "../../../matrix.hpp"
#include <iostream>

template <arithmetric T>
void printM (Matrix<T> M) {
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
  Matrix<float> A = Matrix<float>(4, 4, new float[16] {
    1,1,1,1,
    2,2,2,3,
    4,2,1,1,
    5,2,2,4
  }, true);

  std::cout << "poly 1:" << std::endl;
  float arr1[3] = {24.f, 6.f, 1.f};
  Polynomial a(arr1, 3);
  std::cout << a.to_string() << std::endl;
  printM(a(A));

  return 0;
}
