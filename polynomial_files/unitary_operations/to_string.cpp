#include "../../polynomial.hpp"

std::string Polynomial::to_string () {
  std::string str = "";
  std::string coef = "";
  if (this->size == 0) {
    return "0";
  }
  for (const auto & [coef, grade]: std::ranges::views::zip (
        std::span<float> ((float *)this->coefficients.data (), this->size),
        std::span<uint32_t> ((uint32_t *)this->grades.data (), this->size) | 
          std::ranges::views::transform([] (uint32_t i) {return std::to_string(i);})
      )
    ) {
    if (coef == 1) {
      str = "+ x^" + grade + " " + str;
    } else if (coef == -1) {
      str = "- x^" + grade + " " + str;
    } else if (coef < 0) {
      str = "- " + std::to_string(-coef) + "*x^" + grade + " " + str;
    } else if (coef > 0) {
      str = "+ " + std::to_string(coef) + "*x^" + grade + " " + str;
    }
  }
  if (str == "") {
    str = "0";
  }
  return str;
}
