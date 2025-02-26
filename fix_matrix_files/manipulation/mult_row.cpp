#include "../../fix_matrix_d.hpp"

void Matrix4::multr (unsigned row, float multiplier) {
  if (--row < 4) {
    _data_[row]._v = _mm_mul_ps(_data_[row]._v, _mm_set1_ps(multiplier));
  }
}
