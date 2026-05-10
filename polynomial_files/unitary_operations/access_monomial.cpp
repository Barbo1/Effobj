#include "../../polynomial.hpp"
#include <cstdint>

float Polynomial::operator[] (unsigned grade) {
  uint32_t * grades = (uint32_t*)this->grades.data();
  uint32_t i = 0;
  while (i < this->size && *grades < grade) { i++; grades++; }
  if (*grades == grade)
    return *((float*)this->coefficients.data() + i);
  else
    return 0.f;
}
