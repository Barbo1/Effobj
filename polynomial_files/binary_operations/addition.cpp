#include "../../polynomial.hpp"
#include <cstddef>
#include <cstdint>
#include <cstring>

Polynomial Polynomial::operator+ (const Polynomial & pol) {
  float * coef1 = (float *)this->coefficients.data ();
  uint32_t* grade1 = (uint32_t *)this->grades.data ();
  float * coef2 = (float *)pol.coefficients.data ();
  uint32_t* grade2 = (uint32_t *)pol.grades.data ();

  std::size_t s = 0;

  // calculating the size
  uint32_t i = 0, j = 0;
  while (i < this->size && j < pol.size) {
    if (*grade1 == *grade2) {
      grade2++; grade1++; i++; j++;
      s += (*(coef2++) + *(coef1++)) != 0.f;
    } else if (*grade1 < *grade2) {
      grade1++; coef1++; s++; i++; 
    } else if (*grade1 > *grade2) {
      grade2++; coef2++; s++; j++;
    }
  }
  if (i < this->size) {
    s += this->size - i;
  } else if (j < pol.size) {
    s += pol.size - j;
  }

  // calculating the coefficients 
  coef1 = (float *)this->coefficients.data ();
  grade1 = (uint32_t *)this->grades.data ();
  coef2 = (float *)pol.coefficients.data ();
  grade2 = (uint32_t *)pol.grades.data ();
  
  std::vector<fv_x8> coefs;
  std::vector<iv_x8> grades;

  std::size_t vec_size = (s + 7) / 8;
  coefs.resize (vec_size);
  grades.resize (vec_size);
  float * coef = (float *)coefs.data ();
  uint32_t * grade = (uint32_t *)grades.data ();

  i = 0, j = 0;
  while (i < this->size && j < pol.size) {
    if (*grade1 == *grade2) {
      i++; j++;
      grade2++;
      uint32_t new_grade = *(grade1++);
      float new_coef = *(coef2++) + *(coef1++);
      if (new_coef != 0.f) {
        *(coef++) = new_coef;
        *(grade++) = new_grade;
      }
    } else if (*grade1 < *grade2) {
      *(grade++) = *(grade1++);
      *(coef++) = *(coef1++);
      i++;
    } else if (*grade1 > *grade2) {
      *(grade++) = *(grade2++);
      *(coef++) = *(coef2++);
      j++;
    }
  }
  if (i < this->size) {
    std::memcpy(grade, grade1, (this->size - i) * sizeof(uint32_t));
    std::memcpy(coef, coef1, (this->size - i) * sizeof(float));
  }
  if (j < pol.size) {
    std::memcpy(grade, grade2, (pol.size - j) * sizeof(uint32_t));
    std::memcpy(coef, coef2, (pol.size - j) * sizeof(float));
  }

  return Polynomial(coefs, grades, s);
}
