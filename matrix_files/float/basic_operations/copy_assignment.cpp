#include "../../../matrix.hpp"

Matrix<float> Matrix<float>::operator= (const Matrix & M) noexcept {
  _rows_ = M._rows_;
  _columns_ = M._columns_;
  _length_ = M._length_;
  if (_data_ != nullptr) {
    delete [] _data_;
  }
  if(_rows_ != 0 && _columns_ != 0) {
    unsigned length = _rows_*_length_;
    _data_ = new fv_x4[length];
    memcpy(_data_, M._data_, sizeof(fv_x4)*length);
  } else {
    _data_ = nullptr;
  }
  return *this;
}
