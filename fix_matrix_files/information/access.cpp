#include "../../fix_matrix_d.hpp"

float Matrix4::operator() (unsigned row, unsigned column) const {
  if (--row < 4 && --column < 4) {
    return _data_[row]._f[column];
  }
  return 0;
}
