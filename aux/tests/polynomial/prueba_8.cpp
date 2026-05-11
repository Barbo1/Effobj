#include "../../../polynomial.hpp"
#include <iostream>

int main () {
  std::cout << "poly 1:" << std::endl;
  float arr1[3] = {24.f, 6.f, 1.f};
  Polynomial a(arr1, 3);
  std::cout << a.to_string() << std::endl;
  std::cout << a(1.f) << std::endl;

  std::cout << std::endl;
  std::cout << "poly 2:" << std::endl;
  float arr2[7] = {24.f, 0.f, 1.f, 0.f, 0.f, 13.f, 5.f};
  Polynomial b(arr2, 7);
  std::cout << b.to_string() << std::endl;
  std::cout << b(-2.f) << std::endl;

  std::cout << std::endl;
  std::cout << "poly 3:" << std::endl;
  float arr3[7] = {0.f, 0.f, 1.f, 0.f, 0.f, 13.f, 5.f};
  Polynomial c(arr3, 7);
  std::cout << c.to_string() << std::endl;
  std::cout << c(-2.f) << std::endl;

  return 0;
}
