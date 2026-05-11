#include "../../../polynomial.hpp"
#include <iostream>

int main () {
  float arr1[3] = {24.f, 6.f, 1.f};
  Polynomial a(arr1, 3);
  std::cout << a.to_string() << std::endl;
  std::cout << a.integrate().to_string() << std::endl;
  std::cout << a.integrate().to_string() << std::endl;
  std::cout << a.derivate().to_string() << std::endl;
  std::cout << a.derivate().to_string() << std::endl;
  return 0;
}
