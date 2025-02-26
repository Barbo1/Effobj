#include "../../../matrix.hpp"

void Matrix<float>::changec (unsigned col1, unsigned col2) {
  col1--;
  col2--;
  if (col1 <= _columns_ && col2 <= _columns_ && col1 != col2) {  
    for (unsigned i = 0; i < _rows_; i++) {
      std::swap(
        _data_[i*_length_ + col1 / 4]._f[col1 % 4], 
        _data_[i*_length_ + col2 / 4]._f[col2 % 4]
      );
    }
  }
}
