#include "../../../matrix.hpp"

Matrix<float> Matrix<float>::operator=(Matrix && M) noexcept {
  delete [] _data_;
  _data_ = std::exchange(M._data_, nullptr);
  _rows_ = M._rows_;
  _columns_ = M._columns_;
  _length_ = M._length_;
  return *this;
}
