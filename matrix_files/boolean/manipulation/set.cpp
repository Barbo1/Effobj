#include "../../../matrix.hpp"

void Matrix<bool>::set (unsigned row, unsigned column) {
  row--;
  column--;
  if (static_cast<int64_t>(row) < _rows_ && static_cast<int64_t>(column) < _columns_) {
    _data_ [(row >> 3) * _lenc_ + (column >> 3)] ^= 1ULL << (((row & 7) << 3) + (column & 7));
  }
}
