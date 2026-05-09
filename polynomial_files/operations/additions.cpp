#include "../../polynomial.hpp"
#include <cstddef>

Polynomial Polynomial::operator+ (const Polynomial & pol) {
  float * coef1 = (float *)this->coefficients.data ();
  uint32_t* grade1 = (uint32_t *)this->grades.data ();
  uint32_t* grade1f = (uint32_t *)this->grades.data () + this->size;
  float * coef2 = (float *)pol.coefficients.data ();
  uint32_t* grade2 = (uint32_t *)pol.grades.data ();
  uint32_t* grade2f = (uint32_t *)pol.grades.data () + pol.size;

  std::size_t vec_size = (this->size + pol.size) / 8, s = 0;
  std::vector<fv_x8> coefs;
  std::vector<iv_x8> grades;
  coefs.reserve (vec_size);
  grades.reserve (vec_size);
  float * coef = (float *)coefs.data ();
  uint32_t * grade = (uint32_t *)grades.data ();

  while (grade1 < grade1f && grade2 < grade2f) {
    s++;
    if (*grade1 == *grade2) {
      grade2++;
      *(grade++) = *(grade1++);
      *(coef++) = *(coef2++) + *(coef1++);
    } else if (*grade1 < *grade2) {
      *(grade++) = *(grade1++);
      *(coef++) = *(coef1++);
    } else if (*grade1 > *grade2) {
      *(grade++) = *(grade2++);
      *(coef++) = *(coef2++);
    }
  }
  if (grade1 < grade1f) {
    s += grade1f - grade2;
    while (grade1 < grade1f) {
      *(grade++) = *(grade1++);
      *(coef++) = *(coef1++);
    }
  }
  if (grade2 < grade2f) {
    s += grade2f - grade2;
    while (grade2 < grade2f) {
      *(grade++) = *(grade2++);
      *(coef++) = *(coef2++);
    }
  }

  return Polynomial(coefs, grades, s);
}
