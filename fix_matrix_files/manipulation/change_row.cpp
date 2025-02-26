#include "../../fix_matrix_d.hpp"

void Matrix4::changer (unsigned row1, unsigned row2) {
  row1--;
  row2--;
  if(row1 < 4 && row2 < 4 && row1 != row2) {
    std::swap(_data_[row1]._v, _data_[row2]._v);
  }
}
