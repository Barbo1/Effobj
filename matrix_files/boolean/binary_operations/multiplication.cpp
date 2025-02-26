#include "../../../matrix.hpp"

Matrix<bool> Matrix<bool>::operator*(const Matrix & A) const {
  if (_columns_ == A._rows_) {
    uint64_t data_val, res, one = 1;
    uint64_t * _data_new_ = new uint64_t[_lenr_ * A._lenc_];
    for (int i = 0; i < _lenr_ - 1; i++) {
      for (int j = 0, index = i * _lenc_; j < A._lenc_; j++, index++) {
        multiply_by_index (i, j, 8, _lenc_, index, _data_, A._data_, _data_new_);
      }
    }
    /* Last iteration separated because (I think) is needed. */
    for (int j = 0, index = (_lenr_ - 1) * _lenc_; j < A._lenc_; j++, index++) {
      multiply_by_index (_lenr_ - 1, j, _rows_ & 7, _lenc_, index, _data_, A._data_, _data_new_);
    }
    return Matrix(_rows_, A._columns_, _data_new_);
  }
  return Matrix();
}
