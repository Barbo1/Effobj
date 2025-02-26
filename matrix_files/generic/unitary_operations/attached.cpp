#include "../../../matrix.hpp"

template<arithmetric T>
Matrix<T> Matrix<T>::attached(unsigned row_to_elim, unsigned col_to_elim) {
  row_to_elim--;
  col_to_elim--;
  if(row_to_elim <= _rows_ && col_to_elim <= _columns_) {
    int i, j, pos_i, pos_j;
    int _rows_new_ = _rows_-1, _columns_new_ = _columns_-1;
    T * _data_new_ = new T[_rows_new_*_columns_new_];
    for(i = 0; i < _rows_; i++) {
      pos_i = i - (i > row_to_elim);
      for(j = 0; j < _columns_; j++) {
        pos_j = j - (j > col_to_elim);
        if(i != row_to_elim && j != col_to_elim) {
          _data_new_[_rows_new_*pos_i + pos_j] = _data_[_rows_*i + j];
        }
      }
    }
    return Matrix(_rows_new_, _columns_new_, _data_new_, true);
  } else {
    return Matrix();
  }
}
