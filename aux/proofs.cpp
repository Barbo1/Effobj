#include "../fix_matrix_d.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main () {
  /*
  int n = 15000;
  float t = clock ();
  for (int i = 0; i < n; i++) {
    Matrix4 A = Matrix4(new float[16] {
      (float)rand(), (float)rand(), (float)rand(), (float)rand(),
      (float)rand(), (float)rand(), (float)rand(), (float)rand(),
      (float)rand(), (float)rand(), (float)rand(), (float)rand(),
      (float)rand(), (float)rand(), (float)rand(), (float)rand()
    });
    A.determinant ();
  }
  std::cout 
    << std::endl 
    << "determinant calculations with " 
    << n 
    << " iterations: " 
    << ((clock () - t) / CLOCKS_PER_SEC) 
    << "s"
    << std::endl;
  */

  Matrix4 A = Matrix4 (new float [16] {
    5, 7, 9, 10,
    2, 3, 3, 8,
    8, 10, 2, 3,
    3, 3, 4, 8
  });

  Matrix4 B = Matrix4 (new float [16] {
    3, 10, 12, 18,
    12, 1, 4, 9,
    9, 10, 12, 2,
    3, 12, 4, 10
  });

  Matrix4 C = A * B;
  
  std::cout << "comprobacion: " << std::endl;
  for (int i = 1; i < 5; i++) {
    for (int j = 1; j < 5; j++) {
      std::cout << C (i, j) << ", ";
    }
    std::cout << std::endl;
  }
}
