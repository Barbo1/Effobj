#include "../../../matrix.hpp"

void Matrix<bool>::set (unsigned row, unsigned column) {
  row--;
  column--;
  if (row < _rows_ && column < _columns_) {
    uint64_t one = 1;
    _data_ [(row >> 3) * _lenc_ + (column >> 3)] ^= one << ((row & 7) << 3) + (column & 7);
  }
}
