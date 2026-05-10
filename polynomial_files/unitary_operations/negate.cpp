#include "../../polynomial.hpp"
#include <cstdint>

Polynomial Polynomial::operator- () {
  for (uint32_t i = 0; i < (this->size + 7) / 8; i++) {
    this->coefficients[i]._v = _mm256_xor_ps (
      this->coefficients[i]._v,
      _mm256_set1_ps(-0.f)
    );
  }
  return *this;
}
