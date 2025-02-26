#include "../../../matrix.hpp"

Matrix<bool> Matrix<bool>::operator=(const Matrix & M) noexcept {
  _rows_ = M._rows_;
  _columns_ = M._columns_;
  _lenr_ = M._lenr_;
  _lenc_ = M._lenc_;
  int top = _lenr_ * _lenc_;
  if (top != 0){
    if (_data_ != nullptr) {
      delete [] _data_;
    }
    _data_ = new uint64_t[top];
    std::memcpy (_data_, M._data_, sizeof(uint64_t) * top);
  } else {
    _data_ = nullptr;
  }
  return *this;
}
