#include "../../../matrix.hpp"

void Matrix<float>::multc (unsigned column, float multiplier) { 
  column--;
  if (column <= _columns_) {
    for (unsigned i = 0; i < _rows_; i++) {
      _data_[(_length_*i + column / 4) / 4]._f[column % 4] *= multiplier;
    }
  }
}
