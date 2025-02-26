#include "../../fix_matrix_d.hpp"

Matrix4 Matrix4::operator* (const Matrix4 & A) {
  fv_x4 * _data_new_  = new fv_x4[4];
  fv_x4 * _tras_ = new fv_x4[4];
  fv_x4 res;

  // create traspose matrix.
  _tras_[0]._f[0] = A._data_[0]._f[0];
  _tras_[0]._f[1] = A._data_[1]._f[0];
  _tras_[0]._f[2] = A._data_[2]._f[0];
  _tras_[0]._f[3] = A._data_[3]._f[0];

  _tras_[1]._f[0] = A._data_[0]._f[1];
  _tras_[1]._f[1] = A._data_[1]._f[1];
  _tras_[1]._f[2] = A._data_[2]._f[1];
  _tras_[1]._f[3] = A._data_[3]._f[1];

  _tras_[2]._f[0] = A._data_[0]._f[2];
  _tras_[2]._f[1] = A._data_[1]._f[2];
  _tras_[2]._f[2] = A._data_[2]._f[2];
  _tras_[2]._f[3] = A._data_[3]._f[2];

  _tras_[3]._f[0] = A._data_[0]._f[3];
  _tras_[3]._f[1] = A._data_[1]._f[3];
  _tras_[3]._f[2] = A._data_[2]._f[3];
  _tras_[3]._f[3] = A._data_[3]._f[3];

  // do the multipication.
  // row 1
  res._v = _mm_mul_ps(_data_[0]._v, _tras_[0]._v);
  _data_new_[0]._f[0] = res._f[0] + res._f[1] + res._f[2] + res._f[3];

  res._v = _mm_mul_ps(_data_[0]._v, _tras_[1]._v);
  _data_new_[0]._f[1] = res._f[0] + res._f[1] + res._f[2] + res._f[3];

  res._v = _mm_mul_ps(_data_[0]._v, _tras_[2]._v);
  _data_new_[0]._f[2] = res._f[0] + res._f[1] + res._f[2] + res._f[3];

  res._v = _mm_mul_ps(_data_[0]._v, _tras_[3]._v);
  _data_new_[0]._f[3] = res._f[0] + res._f[1] + res._f[2] + res._f[3];

  // row 2
  res._v = _mm_mul_ps(_data_[1]._v, _tras_[0]._v);
  _data_new_[1]._f[0] = res._f[0] + res._f[1] + res._f[2] + res._f[3];

  res._v = _mm_mul_ps(_data_[1]._v, _tras_[1]._v);
  _data_new_[1]._f[1] = res._f[0] + res._f[1] + res._f[2] + res._f[3];

  res._v = _mm_mul_ps(_data_[1]._v, _tras_[2]._v);
  _data_new_[1]._f[2] = res._f[0] + res._f[1] + res._f[2] + res._f[3];

  res._v = _mm_mul_ps(_data_[1]._v, _tras_[3]._v);
  _data_new_[1]._f[3] = res._f[0] + res._f[1] + res._f[2] + res._f[3];

  // row 3
  res._v = _mm_mul_ps(_data_[2]._v, _tras_[0]._v);
  _data_new_[2]._f[0] = res._f[0] + res._f[1] + res._f[2] + res._f[3];

  res._v = _mm_mul_ps(_data_[2]._v, _tras_[1]._v);
  _data_new_[2]._f[1] = res._f[0] + res._f[1] + res._f[2] + res._f[3];

  res._v = _mm_mul_ps(_data_[2]._v, _tras_[2]._v);
  _data_new_[2]._f[2] = res._f[0] + res._f[1] + res._f[2] + res._f[3];

  res._v = _mm_mul_ps(_data_[2]._v, _tras_[3]._v);
  _data_new_[2]._f[3] = res._f[0] + res._f[1] + res._f[2] + res._f[3];

  // row 4 
  res._v = _mm_mul_ps(_data_[3]._v, _tras_[0]._v);
  _data_new_[3]._f[0] = res._f[0] + res._f[1] + res._f[2] + res._f[3];

  res._v = _mm_mul_ps(_data_[3]._v, _tras_[1]._v);
  _data_new_[3]._f[1] = res._f[0] + res._f[1] + res._f[2] + res._f[3];

  res._v = _mm_mul_ps(_data_[3]._v, _tras_[2]._v);
  _data_new_[3]._f[2] = res._f[0] + res._f[1] + res._f[2] + res._f[3];

  res._v = _mm_mul_ps(_data_[3]._v, _tras_[3]._v);
  _data_new_[3]._f[3] = res._f[0] + res._f[1] + res._f[2] + res._f[3];

  // return.
  delete [] _tras_;
  return Matrix4(_data_new_);
}
