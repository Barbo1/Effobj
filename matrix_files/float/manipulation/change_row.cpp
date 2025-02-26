#include "../../../matrix.hpp"

void Matrix<float>::changer(unsigned row1, unsigned row2) {
  row1--;
  row2--;
  if (row1 <= _rows_ && row2 <= _rows_ && row1 != row2) {
    for (unsigned i = 0; i < _length_; i++) {
      std::swap(_data_[_length_*row1 + i]._v, _data_[_length_*row2 + i]._v);
    }
  }
}
