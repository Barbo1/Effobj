#include "../../../matrix.hpp"

template<arithmetric T>
T& Matrix<T>::operator()(unsigned row, unsigned column) const {
  row--;
  column--;
  return _data_[_rows_*row + column];
}
