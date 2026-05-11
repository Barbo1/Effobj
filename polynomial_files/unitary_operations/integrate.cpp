#include "../../polynomial.hpp"
#include <cstdint>
#include <immintrin.h>

Polynomial Polynomial::integrate () {
  __m256i ones_i = _mm256_set1_epi32(1);
  for (uint32_t i = 0; i < (this->size + 7) / 8; i++) {
    this->grades[i]._v = _mm256_add_epi32(this->grades[i]._v, ones_i);
    this->coefficients[i]._v = _mm256_div_ps(
      this->coefficients[i]._v,
      _mm256_cvtepi32_ps(this->grades[i]._v)
    );
  }

  return *this;
}
