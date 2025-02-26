#include "../../../matrix.hpp"

/*
 *  Multiply the column referenced by 'column' by 'multiplier'.
 * */
template <arithmetric T>
void Matrix<T>::multr(unsigned row, float multiplier) {
  row--;
  if (row <= _rows_) { 
    for (unsigned i = _columns_ * row; i < _columns_ * (row + 1); i++) {
      _data_[i] *= multiplier;
    }
  }
}
