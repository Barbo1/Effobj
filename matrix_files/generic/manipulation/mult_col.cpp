#include "../../../matrix.hpp"

/*
 *  Multiply the column referenced by 'column' by 'multiplier'.
 * */
template <arithmetric T>
void Matrix<T>::multc(unsigned column, float multiplier) { 
  column--;
  if (column <= _columns_) {
    for (unsigned i = 0; i < _rows_; i++) {
      _data_[_columns_*i + column] *= multiplier;
    }
  }
}
