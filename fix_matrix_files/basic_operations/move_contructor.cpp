#include "../../fix_matrix_d.hpp"

Matrix4::Matrix4 (Matrix4 && A) {
  _data_ = A._data_;
  A._data_ = nullptr;
}
