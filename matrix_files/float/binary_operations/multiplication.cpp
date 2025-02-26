#include "../../../matrix.hpp"

Matrix<float> Matrix<float>::operator* (const Matrix & A) const {
  if (_columns_ == A._rows_) {
    unsigned i, j, k;
    __m128 res_1, zero = _mm_setzero_ps();
    fv_x4 * _res_, * _data_new_;

    _res_ = new fv_x4[A._columns_ * _length_];
    for (i = 0; i < A._columns_; i++) {
      _res_[_length_*(i+1) - 1]._v = zero;
      for (j = 0; j < A._rows_; j++) {
        _res_[_length_*i + j/4]._f[j % 4] = A._data_[A._length_*j + i/4]._f[i % 4];
      }
    }

    _data_new_ = new fv_x4[_rows_ * A._length_];
    for (i = 0; i < _rows_; i++) {
      for (j = 0; j < _rows_; j++) {
        res_1 = zero;
        for (k = 0; k < _length_; k++) {
          res_1 = _mm_add_ps (
              res_1,
              _mm_mul_ps(
                _data_[_length_*i + k]._v, 
                _res_[_length_*j + k]._v
              )
            );
        }
        _data_new_[i*A._length_ + j/4]._f[j % 4] = 
          res_1[0] + 
          res_1[1] + 
          res_1[2] + 
          res_1[3];
      }
    }
    delete [] _res_;
    return Matrix(_rows_, A._columns_, _data_new_);
  } else {
    return Matrix();
  }
}
