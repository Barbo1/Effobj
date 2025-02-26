#include "../../fix_matrix_d.hpp"

Matrix4 Matrix4::traspose () {
  fv_x4 * _data_new_ = new fv_x4[4];

  _data_new_[0]._f[0] = _data_[0]._f[0];
  _data_new_[0]._f[1] = _data_[1]._f[0];
  _data_new_[0]._f[2] = _data_[2]._f[0];
  _data_new_[0]._f[3] = _data_[3]._f[0];

  _data_new_[1]._f[0] = _data_[0]._f[1];
  _data_new_[1]._f[1] = _data_[1]._f[1];
  _data_new_[1]._f[2] = _data_[2]._f[1];
  _data_new_[1]._f[3] = _data_[3]._f[1];

  _data_new_[2]._f[0] = _data_[0]._f[2];
  _data_new_[2]._f[1] = _data_[1]._f[2];
  _data_new_[2]._f[2] = _data_[2]._f[2];
  _data_new_[2]._f[3] = _data_[3]._f[2];

  _data_new_[3]._f[0] = _data_[0]._f[3];
  _data_new_[3]._f[1] = _data_[1]._f[3];
  _data_new_[3]._f[2] = _data_[2]._f[3];
  _data_new_[3]._f[3] = _data_[3]._f[3];

  return Matrix4(_data_new_);
}
