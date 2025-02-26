#include "../../../matrix.hpp"

void Matrix<bool>::multr(unsigned row, bool multiplier) {
  row--;
  if (row < _rows_ && !multiplier) {
    uint64_t mask = Matrix::rvm[row & 7];
    row >>= 3;
    for (int i = _lenc_ * row; i < _lenc_ * (row + 1); i++) {
      _data_[i] &= ~mask;
    }
  }
}

