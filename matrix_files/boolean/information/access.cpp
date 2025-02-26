#include "../../../matrix.hpp"

bool Matrix<bool>::operator()(unsigned row, unsigned column) const {
  row--;
  column--;
  if (row < _rows_ && column < _columns_) {
    uint64_t one = 1;
    return _data_[(row >> 3)*_lenc_ + (column >> 3)] & (one << ((row & 7) << 3) + (column & 7));
  }
  return 0;
}
