#include "../../../matrix.hpp"

Matrix<float> Matrix<float>::traspose () {
  if(_columns_ != 0 && _rows_ != 0) {
    unsigned i, j;
    __m128 zero = _mm_setzero_ps();
    unsigned length = (_rows_ + 3)/4;
    fv_x4 * _data_new_ = new fv_x4[_columns_ * length];
    for(i = 0; i < _columns_; i++) {
      _data_new_[length*(i+1) - 1]._v = zero;
      for(j = 0; j < _rows_; j++) {
        _data_new_[length*i + j/4]._f[j % 4] = _data_[_length_*j + i/4]._f[i % 4];
      }
    }
    return Matrix(_columns_, _rows_, _data_new_);
  } else {
    return Matrix();
  }
}
