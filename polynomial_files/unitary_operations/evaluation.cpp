#include "../../polynomial.hpp"
#include "../../matrix.hpp"
#include <immintrin.h>
#include <cstdint>
#include <bit>

int64_t maxi (int64_t f1, int64_t f2) {
  int64_t c = (f1 - f2) >> 63;
  return (~c & f1) | (c & f2);
}

template <semi_arithmetric X>
X evaluate_polynomial(const Polynomial pol, const X& obj, const X& one, const X& zero) {

  // calculate max difference between consecutive terms.
  int64_t max_diff = 0;
  uint32_t* grade = (uint32_t *)pol.grades.data ();
  for (uint32_t i = 1; i < pol.size; i++) {
    int64_t next_diff = *(grade + 1) - *grade;
    max_diff = maxi(max_diff, next_diff);
  }

  // generate array of potences.
  int32_t l2 = 32 - std::countl_zero(static_cast<uint32_t>(max_diff));
  X * arr = new X[l2];
  arr[0] = obj;
  for (uint32_t i = 0; i < static_cast<uint32_t>(l2); i++)
    arr[i+1] = arr[i] * arr[i];

  // calculating the returned value.
  float * coef = (float *)pol.coefficients.data ();
  grade = (uint32_t *)pol.grades.data ();
  X current_x = one;
  X current_ret = zero;
  uint32_t init = 0;
  if (*grade == 0){
    current_ret = one * *coef++;
    grade++;
    init = 1;
  }

  for (uint32_t i = init; i < pol.size; i++) {
    int64_t next_diff = *grade - *(grade - 1);
    X x_diff = one;
    for (uint32_t j = 0; j < static_cast<uint32_t>(l2); j++)
      if ((1 << j) & next_diff)
        x_diff *= arr[j];
    current_x *= x_diff;
    current_ret += current_x * (*coef++);
    grade++;
  }

  delete [] arr;
  return current_ret;
}

float Polynomial::operator()(const float& x) {
  return evaluate_polynomial<float>(*this, x, 1.f, 0.f);
}

Matrix<float> Polynomial::operator()(const Matrix<float>& x) {
  Matrix<float> zero = mfo<float>(0, x.rows(), x.rows());
  if (x.cols() != x.rows()) {
    return zero;
  }
  Matrix<float> one = identity<float>(x.rows());
  return evaluate_polynomial<Matrix<float>>(*this, x, one, zero);
}
