#include "../../../matrix.hpp"

void Matrix<bool>::changer(unsigned row1, unsigned row2) {
  row1--;
  row2--;
  if (row1 < _rows_ && row2 < _rows_ && row1 != row2) {
    uint64_t mask1 = row1 & 7;
    uint64_t mask2 = row2 & 7;
    if (mask2 > mask1) {
      std::swap (mask1, mask2);
      std::swap (row1, row2);
    }
    int k = (mask1 - mask2) << 3;
    mask1 = Matrix::rvm[mask1];
    mask2 = Matrix::rvm[mask2];
    row1 = row1 >> 3;
    row2 = row2 >> 3;

    if (row2 == row1) {
      uint64_t t;
      mask1 = ~(mask1 | mask2);
      for (int i = _lenc_ * row1; i < _lenc_ * (row1 + 1); i++) {
        t = _data_[i];
        _data_[i] = (t & mask1) | ((t & mask2) << k) | ((t >> k) & mask2);
      }
    } else {
      uint64_t t1, t2;
      for (int i = 0; i < _lenc_; i++) {
        t1 = _data_[i + row1];
        t2 = _data_[i + row2];
        _data_[i + row1] = t1 & ~mask1 | (t2 & mask2) << k;
        _data_[i + row2] = t2 & ~mask2 | (t1 & mask1) >> k;
      }
    }
  }
}
