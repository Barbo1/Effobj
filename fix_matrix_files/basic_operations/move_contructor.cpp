#include "../../fix_matrix_d.hpp"

Matrix4::Matrix4 (Matrix4 && A) {
  this->_data_ = std::exchange (A._data_, nullptr);
}
