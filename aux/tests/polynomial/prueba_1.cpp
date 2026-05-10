#include "../../../polynomial.hpp"
#include <iostream>

int main () {
  Polynomial a(1);
  Polynomial b(2.f, 2);
  Polynomial c(a + b);
  std::cout << a.to_string() << std::endl;
  std::cout << (-b).to_string() << std::endl;
  std::cout << c.to_string() << std::endl;
  return 0;
}
