#include "../../../polynomial.hpp"
#include <iostream>

int main () {
  float arr1[7] = {1.5f, 0.f, -1.f, 0.f, 0.f, 1.f, 1.f};
  Polynomial a(arr1, 7);
  std::cout << a.to_string() << std::endl;
  std::cout << a.derivate().to_string() << std::endl;
  std::cout << a.derivate().derivate().to_string() << std::endl;
  return 0;
}
