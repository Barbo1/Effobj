#include "../../fix_matrix_d.hpp"

Matrix4::Matrix4 (float * data_) {
  _data_ = new fv_x4[4];

  _data_[0]._f[0] = data_[0];
  _data_[0]._f[1] = data_[1];
  _data_[0]._f[2] = data_[2];
  _data_[0]._f[3] = data_[3];

  _data_[1]._f[0] = data_[4];
  _data_[1]._f[1] = data_[5];
  _data_[1]._f[2] = data_[6];
  _data_[1]._f[3] = data_[7];

  _data_[2]._f[0] = data_[8];
  _data_[2]._f[1] = data_[9];
  _data_[2]._f[2] = data_[10];
  _data_[2]._f[3] = data_[11];

  _data_[3]._f[0] = data_[12];
  _data_[3]._f[1] = data_[13];
  _data_[3]._f[2] = data_[14];
  _data_[3]._f[3] = data_[15];

  delete [] data_;
}
