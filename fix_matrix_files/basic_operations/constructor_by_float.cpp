#include "../../fix_matrix.hpp"

Matrix4::Matrix4 (float * data_) {
  for (uint32_t i = 0; i < 16; i++) {
    _data_[i >> 2]._f[i & 3] = data_[i];
  }
}
