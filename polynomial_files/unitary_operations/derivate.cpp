#include "../../polynomial.hpp"
#include <cstdint>
#include <immintrin.h>

Polynomial Polynomial::derivate () {
  // quiting independent term
  __m256i grade_perm = _mm256_set_epi32(0,7,6,5,4,3,2,1);
  if (this->grades[0]._i[0] == 0) {
    uint32_t i = 0;
    while (i < (this->size - 1) / 8) {
      this->coefficients[i]._v = _mm256_blend_ps (
        _mm256_permutevar8x32_ps(this->coefficients[i]._v, grade_perm),
        _mm256_permutevar8x32_ps(this->coefficients[i+1]._v, grade_perm),
        0b10000000
      );
      this->grades[i]._v = _mm256_blend_epi32 (
        _mm256_permutevar8x32_epi32(this->grades[i]._v, grade_perm),
        _mm256_permutevar8x32_epi32(this->grades[i+1]._v, grade_perm),
        0b10000000
      );
      i++;
    }
    this->coefficients[i]._v = _mm256_permutevar8x32_ps(this->coefficients[i]._v, grade_perm);
    this->grades[i]._v = _mm256_permutevar8x32_epi32(this->grades[i]._v, grade_perm);
    if ((this->size & 0b111) == 0b1) {
      this->coefficients.pop_back();
      this->grades.pop_back();
    }
  }

  // modifying monomials.
  this->size--;
  __m256i ones_i = _mm256_set1_epi32(1);
  for (uint32_t i = 0; i < (this->size + 7) / 8; i++) {
    this->coefficients[i]._v = _mm256_mul_ps(
      _mm256_cvtepi32_ps(this->grades[i]._v), 
      this->coefficients[i]._v
    );
    this->grades[i]._v = _mm256_sub_epi32(this->grades[i]._v, ones_i);
  }

  return *this;
}
