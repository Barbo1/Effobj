#include "../../fix_matrix.hpp"

Matrix4 Matrix4::operator* (float multiplier) {
  __m128 res = _mm_set1_ps(multiplier);

  this->_data_[0]._v = _mm_mul_ps(res, this->_data_[0]._v);
  this->_data_[1]._v = _mm_mul_ps(res, this->_data_[1]._v);
  this->_data_[2]._v = _mm_mul_ps(res, this->_data_[2]._v);
  this->_data_[3]._v = _mm_mul_ps(res, this->_data_[3]._v);

  return *this;
}
