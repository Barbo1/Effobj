#include "../../polynomial.hpp"
#include <utility>

Polynomial::Polynomial (Polynomial && pol) {
  this->size = std::exchange (pol.size, 0);
  this->coefficients = std::exchange (
    pol.coefficients, 
    std::vector<fv_x8>()
  );
  this->grades = std::exchange (
    pol.grades, 
    std::vector<iv_x8>()
  );
}
