#include "../../polynomial.hpp"

Polynomial::Polynomial (const Polynomial & pol) {
  this->size = pol.size;
  this->coefficients = std::vector<fv_x8>(pol.coefficients);
  this->grades = std::vector<iv_x8>(pol.grades);
}
