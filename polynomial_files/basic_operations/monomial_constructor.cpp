#include "../../polynomial.hpp"

Polynomial::Polynomial (float coefficient, uint64_t grade) {
  this->size = 1;
  this->coefficients = std::vector<fv_x8> { (fv_x8) _mm256_set_ps (0,0,0,0,0,0,0,coefficient) };
  this->grades = std::vector<iv_x8> { (iv_x8) _mm256_set_ps (0,0,0,0,0,0,0,grade) };
}
