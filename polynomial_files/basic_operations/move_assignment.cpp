#include "../../polynomial.hpp"
#include <utility>

Polynomial& Polynomial::operator= (Polynomial && pol) {
  this->size = std::exchange (pol.size, 0);
  this->coefficients = std::exchange (
    pol.coefficients, 
    std::vector<fv_x8>{ (fv_x8) _mm256_set_ps (0,0,0,0,0,0,0,0) }
  );
  this->grades = std::exchange (
    pol.grades, 
    std::vector<iv_x8>{ (iv_x8) _mm256_set_epi32 (0,0,0,0,0,0,0,0) }
  );
  return *this;
}
