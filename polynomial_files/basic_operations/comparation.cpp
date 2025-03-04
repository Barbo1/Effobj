#include "../../polynomial.hpp"

bool Polynomial::operator== (const Polynomial & pol) {
  if (this->size == pol.size) {
    for (const auto & [cv1, cv2]: std::ranges::views::zip (this->coefficients, pol.coefficients)) {
      if (_mm256_movemask_epi8 (_mm256_cmp_ps (cv1._v, cv2._v, 4))) {
        return false;
      }
    }
    for (const auto & [cv1, cv2]: std::ranges::views::zip (this->grades, pol.grades)) {
      if (_mm256_movemask_epi8 (_mm256_cmp_ps (cv1._v, cv2._v, 4))) {
          return false;
      }
    }
  }
  return true;
}
