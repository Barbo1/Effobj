#include "../../../polynomial.hpp"
#include <iostream>

int main () {
  float arr1[11] = {1.5f, 1.f, -1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f};
  Polynomial a(arr1, 11);
  std::cout << a.to_string() << std::endl;
  std::cout << a.derivate().to_string() << std::endl;
  std::cout << a.derivate().to_string() << std::endl;
  std::cout << a.derivate().to_string() << std::endl;
  std::cout << a.derivate().to_string() << std::endl;
  std::cout << a.derivate().to_string() << std::endl;
  return 0;
}
