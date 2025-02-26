#include "../../../matrix.hpp"

template <arithmetric T>
void Matrix<T>::changec(unsigned col1, unsigned col2) {
  col1--;
  col2--;
  if (col1 <= _columns_ && col2 <= _columns_ && col1 != col2) {  
    for (unsigned i = 0; i < _rows_; i++) {
      std::swap(_data_[_rows_*i + col1], _data_[_rows_*i + col2]);
    }
  }
}
