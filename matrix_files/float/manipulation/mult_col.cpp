#include "../../../matrix.hpp"

void Matrix<float>::multc (unsigned column, float multiplier) { 
  column--;
  if (column <= _columns_) {
    unsigned pos, i;
    for (i = 0; i < _rows_; i++) {
      pos = _length_*i + column / 4;
      _data_[pos / 4]._f[column % 4] *= multiplier;
    }
  }
}
