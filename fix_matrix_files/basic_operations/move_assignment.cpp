#include "../../fix_matrix_d.hpp"

Matrix4 Matrix4::operator= (Matrix4 && A) {
  delete [] this->_data_;
  this->_data_ = std::exchange (A._data_, nullptr);
  return *this;
}
