#include "../../../matrix.hpp"

Matrix<bool> Matrix<bool>::operator+(const Matrix & M) const {
  if(_columns_ == M._columns_ && _rows_ == M._rows_) {
    uint64_t * _data_new_ = new uint64_t[_lenr_ * _lenc_];
    for (int i = 0; i < _lenr_ * _lenc_; i++) {
      _data_new_[i] = _data_[i] | M._data_[i];
    }
    return Matrix(_rows_, _columns_, _data_new_);
  } 
  return Matrix();
} 
