#include "../../../polynomial.hpp"
#include <iostream>

int main () {
  float arr1[10] = {1.5f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, -1.f, 0.f, 1.f};
  Polynomial a(arr1, 10);
  std::cout << a.to_string() << std::endl;
  std::cout << a[1] << std::endl;
  std::cout << a[2] << std::endl;
  std::cout << a[3] << std::endl;
  return 0;
}
