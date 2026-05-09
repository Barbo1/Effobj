#include "../../../matrix.hpp"

#include <utility>

Matrix<float> Matrix<float>::operator=(Matrix && M) noexcept {
  std::free (_data_);
  _data_ = std::exchange(M._data_, nullptr);
  _rows_ = M._rows_;
  _columns_ = M._columns_;
  _length_ = M._length_;
  return *this;
}
