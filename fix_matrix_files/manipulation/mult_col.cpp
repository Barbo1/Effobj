#include "../../fix_matrix_d.hpp"

void Matrix4::multc (unsigned col, float multiplier) {
  if (--col < 4) {
    _data_[0]._f[col] *= multiplier;
    _data_[1]._f[col] *= multiplier;
    _data_[2]._f[col] *= multiplier;
    _data_[3]._f[col] *= multiplier;
  }
}
