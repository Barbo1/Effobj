#include "../../../matrix.hpp"

Matrix<bool> Matrix<bool>::traspose() {
  if (_columns_ != 0 && _rows_ != 0) {
    uint64_t * _data_new_ = new uint64_t[_lenr_ * _lenc_], res, mask1;
    for (int i = 0; i < _lenr_; i++) {
      for (int j = 0; j < _lenc_; j++) {
        res = _data_[_lenc_*i + j];
        for (int r = 49, k = 0; k < 7; k++, r -= 7) {
          mask1 = Matrix::tvm[k];
          res = res & ~(mask1 | Matrix::tvm[13 - k]) | (res & mask1) >> r | res << r & mask1;
        }
        _data_new_[_lenr_*j + i] = res;
      }
    }
    return Matrix(_columns_, _rows_, _data_new_);
  }
  return Matrix();
}
