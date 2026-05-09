#include "../../polynomial.hpp"
#include <ranges>

bool Polynomial::operator== (const Polynomial & pol) {
  if (this->size == pol.size) {
    for (const auto & [cv1, cv2]: std::ranges::views::zip (this->coefficients, pol.coefficients)) {
      if (_mm256_movemask_ps(_mm256_cmp_ps(cv1._v, cv2._v, 4))) {
        return false;
      }
    }
    for (const auto & [cv1, cv2]: std::ranges::views::zip (this->grades, pol.grades)) {
      __m256 op = _mm256_castsi256_ps(_mm256_cmpeq_epi32(cv1._v, cv2._v));
      if (~_mm256_movemask_ps(op)) {
        return false;
      }
    }
    return true;
  }
  return false;
}
