#include "../../fix_matrix.hpp"

Matrix4::Matrix4 (fv_x4 * data_) {
  _data_[0]._v = data_[0]._v;
  _data_[1]._v = data_[1]._v;
  _data_[2]._v = data_[2]._v;
  _data_[3]._v = data_[3]._v;
}
