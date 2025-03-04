#include "../../polynomial.hpp"

Polynomial Polynomial::operator+ (const Polynomial & pol) {
  float * coef1 = (float *)this->coefficients.data ();
  uint32_t * grade1 = (uint32_t *)this->grades.data ();
  uint32_t * grade1f = (uint32_t *)this->grades.data () + this->size;
  float * coef2 = (float *)pol.coefficients.data ();
  uint32_t * grade2 = (uint32_t *)pol.grades.data ();
  uint32_t * grade2f = (uint32_t *)pol.grades.data () + this->size;

  std::size_t s = std::ceil((this->size + pol.size) * 0.633974);
  std::vector<fv_x8> coefs;
  coefs.reserve (s / 8);
  std::vector<iv_x8> grades;
  grades.reserve (s / 8);
  float * coef = (float *)coefs.data ();
  uint32_t * grade = (uint32_t *)grades.data ();

  int i = 0, j = 0;
  while (grade1 < grade1f && grade2 < grade2f) {
    if (*grade1 == *grade2) {
      
    }
  }
  return Polynomial();
}
