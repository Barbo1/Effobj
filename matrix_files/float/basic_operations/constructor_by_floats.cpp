#include "../../../matrix.hpp"

Matrix<float>::Matrix (unsigned rows, unsigned columns, float * data, bool consume) noexcept {
  _rows_ = rows;
  _columns_ = columns;
  if (_rows_ != 0 && _columns_ != 0) {
    unsigned i, j;
    _length_ = (_columns_ + 3) / 4;
    _data_ = new fv_x4[_length_ * _rows_];

    // initialize with 0's the last fv_x4
    for (i = 1; i <= _rows_; i++) {
      _data_[i*_length_ - 1]._v = _mm_setzero_ps();
    }

    for (i = 0; i < _rows_; i++) {
      for (j = 0; j < _columns_; j++) {
        _data_[i*_length_ + j/4]._f[j % 4] = data[i*_columns_ + j];
      }
    }
    if (consume) {
      delete [] data;
    }
  }
  data = nullptr;
}
