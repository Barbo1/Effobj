#include "../../polynomial.hpp"

Polynomial::Polynomial (const Polynomial & pol) {
  this->size = pol.size;
  this->coefficients = pol.coefficients;
  this->grades = pol.grades;
}
