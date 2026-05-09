#include "../../../matrix.hpp"

void Matrix<bool>::multc(unsigned column, bool multiplier) { 
  column--;
  if (static_cast<int64_t>(column) < _columns_ && !multiplier) {
    uint64_t mask = Matrix::cvm[column & 7];
    column >>= 3;
    for (int i = column; i < _lenc_ * _lenr_; i += _lenc_) {
      _data_[i] &= ~mask;
    }
  }
}
