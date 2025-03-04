#include "../../fix_matrix_d.hpp"

Matrix4::~Matrix4 () {
  if (_data_ != nullptr) {
    delete [] _data_;
  }
}
