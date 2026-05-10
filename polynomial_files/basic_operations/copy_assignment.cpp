#include "../../polynomial.hpp"

Polynomial& Polynomial::operator= (const Polynomial & pol) {
  this->size = pol.size;
  this->coefficients = pol.coefficients;
  this->grades = pol.grades;
  return *this;
}
