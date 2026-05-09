#include "../../../matrix.hpp"
#include <cstdint>

bool Matrix<bool>::operator()(unsigned row, unsigned column) const {
  row--;
  column--;
  if (row < static_cast<int64_t>(_rows_) && column < static_cast<int64_t>(_columns_)) {
    return _data_[(row >> 3)*_lenc_ + (column >> 3)] & (1ULL << (((row & 7) << 3) + (column & 7)));
  }
  return 0;
}
