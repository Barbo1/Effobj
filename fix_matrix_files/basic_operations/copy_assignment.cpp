#include "../../fix_matrix_d.hpp"

Matrix4 Matrix4::operator= (const Matrix4 & A) {
  delete [] _data_;
  _data_[0]._v = A._data_[0]._v;
  _data_[1]._v = A._data_[1]._v;
  _data_[2]._v = A._data_[2]._v;
  _data_[3]._v = A._data_[3]._v;
  return *this;
}
