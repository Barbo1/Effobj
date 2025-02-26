#include "../../fix_matrix_d.hpp"

Matrix4 Matrix4::operator* (float multiplier) {
  fv_x4 * data = new fv_x4[4];
  __m128 res = _mm_set1_ps(multiplier);

  data[0]._v = _mm_mul_ps(res, _data_[0]._v);
  data[1]._v = _mm_mul_ps(res, _data_[1]._v);
  data[2]._v = _mm_mul_ps(res, _data_[2]._v);
  data[3]._v = _mm_mul_ps(res, _data_[3]._v);

  return Matrix4(data);
}
