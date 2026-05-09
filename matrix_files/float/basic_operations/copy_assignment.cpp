#include "../../../matrix.hpp"

Matrix<float> Matrix<float>::operator= (const Matrix & M) noexcept {
  _rows_ = M._rows_;
  _columns_ = M._columns_;
  _length_ = M._length_;
  if (_data_ != nullptr) {
    std::free(_data_);
  }
  if(_rows_ != 0 && _columns_ != 0) {
    unsigned length = sizeof(fv_x4) * _rows_ * _length_;
    _data_ = static_cast<fv_x4*>(std::aligned_alloc(16, length));
    memcpy(_data_, M._data_, length);
  } else {
    _data_ = nullptr;
  }
  return *this;
}
