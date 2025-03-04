#include "../../polynomial.hpp"

Polynomial::Polynomial () {
  this->size = 0;
  this->coefficients = std::vector<fv_x8>{ (fv_x8) _mm256_set_ps (0,0,0,0,0,0,0,0) };
  this->grades = std::vector<iv_x8>{ (iv_x8) _mm256_set_ps (0,0,0,0,0,0,0,0) };
}
