#include "../../polynomial.hpp"
#include <cstdint>

Polynomial::Polynomial (float* coefficients, uint32_t max_grade) {
  this->size = 0;
  for (uint32_t i = 0; i < max_grade; i++) { this->size += coefficients[i] != 0.f; }
  std::size_t vec_size = (this->size + 7) / 8;

  this->coefficients = std::vector<fv_x8>();
  this->grades = std::vector<iv_x8>();
  this->coefficients.resize(vec_size);
  this->grades.resize(vec_size);
  float* coefs = (float*)this->coefficients.data();
  uint32_t* grades = (uint32_t*)this->grades.data();

  for (uint32_t i = 0; i < max_grade; i++) {
    if (coefficients[i] != 0.f) {
      *coefs++ = coefficients[i];
      *grades++ = i;
    }
  }
}
