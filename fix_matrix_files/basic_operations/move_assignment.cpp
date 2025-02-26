#include "../../fix_matrix_d.hpp"

Matrix4 Matrix4::operator= (Matrix4 && A) {
  delete [] _data_;
  _data_ = A._data_;
  A._data_ = nullptr;
  return *this;
}
