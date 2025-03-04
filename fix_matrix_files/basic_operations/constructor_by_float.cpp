#include "../../fix_matrix_d.hpp"

Matrix4::Matrix4 (float * data_) {
  _data_ = (fv_x4 *) data_;
}
