#include "../../../matrix.hpp"

template<arithmetric T>
Matrix<T> Matrix<T>::traspose() {
  if(_columns_ != 0 && _rows_ != 0) {
    unsigned i, j;
    T * _data_new_ = new T[_columns_*_rows_];
    for(i = 0; i < _rows_; i++) {
      for(j = 0; j < _columns_; j++) {
        _data_new_[_rows_*i + j] = _data_[_rows_*j + i];
      }
    }
    return Matrix(_columns_, _rows_, _data_new_, true);
  } else {
    return Matrix();
  }
}
