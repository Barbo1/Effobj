#include "../fix_matrix_d.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main () {
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

  std::cout
    << "comprobacion: "
    << (Matrix4(new float[16] {
        1, 12, 3, 4,
        5, 6, 7, 8,
        9, 11, 11, 12,
        13, 14, 17, 16
      }).determinant ())
    << std::endl;
}
