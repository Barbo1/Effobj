#include "../../../polynomial.hpp"
#include <iostream>

int main () {
  float arr1[7] = {1.5f, 0.f, -1.f, 0.f, 0.f, 1.f, 1.f};
  float arr2[7] = {2.f, 68.f, 1.f, 1.f, 1.f, 2.f, 2.f};
  Polynomial a(arr1, 7);
  Polynomial b(arr2, 7);
  std::cout << a.to_string() << std::endl;
  std::cout << b.to_string() << std::endl;
  std::cout << (b + a).to_string() << std::endl;
  return 0;
}
