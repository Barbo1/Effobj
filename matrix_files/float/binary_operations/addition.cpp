#include "../../../matrix.hpp"

Matrix<float> Matrix<float>::operator+(const Matrix & M) const {
  if(_columns_ == M._columns_ && _rows_ == M._rows_) {
    unsigned i;
    fv_x4 * _data_new_ = new fv_x4[_rows_*_length_];
    for(i = 0; i < _rows_ * _length_; i++) {
      _data_new_[i]._v = _mm_add_ps(
        M._data_[i]._v,
        _data_[i]._v
      );
    }
    return Matrix(_rows_, _columns_, _data_new_);
  } else {
    return Matrix();
  } 
}
