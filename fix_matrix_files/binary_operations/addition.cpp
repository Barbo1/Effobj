#include "../../fix_matrix_d.hpp"

Matrix4 Matrix4::operator+ (const Matrix4 & A) {
  fv_x4 * data = new fv_x4[4];
  data[0]._v = _mm_add_ps(_data_[0]._v, A._data_[0]._v);
  data[1]._v = _mm_add_ps(_data_[1]._v, A._data_[1]._v);
  data[2]._v = _mm_add_ps(_data_[2]._v, A._data_[2]._v);
  data[3]._v = _mm_add_ps(_data_[3]._v, A._data_[3]._v);
  return Matrix4(data);
}
