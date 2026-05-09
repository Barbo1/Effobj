#include "../../fix_matrix.hpp"

Matrix4 Matrix4::operator+ (const Matrix4& A) {
  this->_data_[0]._v = _mm_add_ps (this->_data_[0]._v, A._data_[0]._v);
  this->_data_[1]._v = _mm_add_ps (this->_data_[1]._v, A._data_[1]._v);
  this->_data_[2]._v = _mm_add_ps (this->_data_[2]._v, A._data_[2]._v);
  this->_data_[3]._v = _mm_add_ps (this->_data_[3]._v, A._data_[3]._v);
  return *this;
}
