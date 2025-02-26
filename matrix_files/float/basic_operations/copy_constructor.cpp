#include "../../../matrix.hpp"

Matrix<float>::Matrix (const Matrix & M) noexcept {
  _rows_ = M._rows_;
  _columns_ = M._columns_;
  _length_ = M._length_;
  unsigned length = _rows_*_length_;
  _data_ = new fv_x4[length];
  memcpy(_data_, M._data_, sizeof(fv_x4)*length);
}
