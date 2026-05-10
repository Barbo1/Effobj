#include "../../../polynomial.hpp"
#include <iostream>

int main () {
  float arr1[10] = {1.5f, 0.f, 0.f, 0.f, 0.f, -14.f, 0.f, 0.f, 9.f, 9.f};
  Polynomial a(arr1, 10);
  std::cout << a.to_string() << std::endl;
  return 0;
}
