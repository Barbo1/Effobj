#include "../../../matrix.hpp"

/*
 *  Change the rows referenced by 'row1' and 'row2'.
 * */
template <arithmetric T>
void Matrix<T>::changer(unsigned row1, unsigned row2) {
  row1--;
  row2--;
  if (row1 <= _columns_ && row2 <= _columns_ && row1 != row2) {
    for (unsigned i = 0; i < _rows_; i++) {
      std::swap(_data_[_rows_*row1 + i], _data_[_rows_*row2 + i]);
    }
  }
}
