#include "../../fix_matrix_d.hpp"

void Matrix4::changec (unsigned col1, unsigned col2) {
  col1--;
  col2--;
  if (col1 < 4 && col2 < 4 && col1 != col2) {
    std::swap(_data_[0]._f[col1], _data_[0]._f[col2]);
    std::swap(_data_[1]._f[col1], _data_[1]._f[col2]);
    std::swap(_data_[2]._f[col1], _data_[2]._f[col2]);
    std::swap(_data_[3]._f[col1], _data_[3]._f[col2]);
  }
}
