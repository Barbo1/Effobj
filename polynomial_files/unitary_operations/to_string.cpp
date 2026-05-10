#include "../../polynomial.hpp"
#include <cstdint>

std::string Polynomial::to_string () {
  std::string str = "";
  std::string coef = "";
  if (this->size == 0) {
    return "0";
  }
  float * coefs = (float *)this->coefficients.data ();
  uint32_t * grades = (uint32_t *)this->grades.data ();
  
  // first step.
  bool sign = *coefs < 0.f;
  std::string new_part;
  float new_coef = std::abs(*coefs);
  if (*grades == 0) {
    str = std::to_string(new_coef);
  } else {
    new_part = "x^" + std::to_string(*grades);
    if (new_coef != 1.f) 
      new_part = std::to_string(new_coef) + "*" + new_part;
    str = new_part + " " + str;
  }

  // next steps.
  for (uint32_t i = 1; i < this->size; i++) {
    if (sign) str = "- " + str;
    else str = "+ " + str;
    coefs++; grades++;
    sign = *coefs < 0.f;

    new_part = "x^" + std::to_string(*grades);
    new_coef = std::abs(*coefs);
    if (new_coef != 1.f) 
      new_part = std::to_string(new_coef) + "*" + new_part;
    str = new_part + " " + str;
  }
  
  if (sign)
    str = "- " + str;

  if (str == "")
    str = "0";
  return str;
}
