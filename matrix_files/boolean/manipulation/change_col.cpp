#include "../../../matrix.hpp"

void Matrix<bool>::changec (unsigned col1, unsigned col2) {
  col1--;
  col2--;
  if (col1 < _columns_ && col2 < _columns_ && col1 != col2) {
    uint64_t mask1 = col1 & 7;
    uint64_t mask2 = col2 & 7;
    if (mask2 > mask1) {
      std::swap (mask1, mask2);
      std::swap (col1, col2);
    }
    int k = mask1 - mask2;
    mask1 = Matrix::cvm[mask1];
    mask2 = Matrix::cvm[mask2];
    col1 = col1 >> 3;
    col2 = col2 >> 3;

    if (col2 == col1) {
      uint64_t t;
      mask1 = ~(mask1 | mask2);
      for (int i = col1; i < _lenr_ * _lenc_; i += _lenc_) {
        t = _data_[i];
        _data_[i] = (t & mask1) | ((t & mask2) << k) | ((t >> k) & mask2);
      }
    } else {
      uint64_t t1, t2;
      for (int i = 0; i < _lenr_ * _lenc_; i += _lenc_) {
        t1 = _data_[i + col1];
        t2 = _data_[i + col2];
        _data_[i + col1] = t1 & ~mask1 | (t2 & mask2) << k;
        _data_[i + col2] = t2 & ~mask2 | (t1 & mask1) >> k;
      }
    }
  }
}
