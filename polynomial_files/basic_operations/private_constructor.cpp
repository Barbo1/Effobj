#include "../../polynomial.hpp"

Polynomial::Polynomial (std::vector<fv_x8>& coefficients, std::vector<iv_x8>& grades, std::size_t size) {
  this->size = size;
  this->coefficients = std::move(coefficients);
  this->grades = std::move(grades);
}
