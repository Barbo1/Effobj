#include "../../../matrix.hpp"

/*
 *  Return the inverse of the Matrix. If this is a null Matrix, or the determinant is 0, a
 *  null Matrix will be returned.
 * */
template <arithmetric T>
Matrix<T> Matrix<T>::invert() {
  Matrix<T> ret = Matrix<T>();
  T onec = 1;
  if (_rows_ != 0 && _columns_ != 0 && _columns_ == _rows_) {
    int current_dim = 0, i, j;
    T cm_1, cm_2;
    bool det_0 = true;

    /* Create a copy of the elements array converted to double. */
    T * _data_res_ = new T[_rows_ * _rows_];
    for (i = 0; i < _rows_; i++) {
      for (j = 0; j < _rows_; j++) {
        _data_res_[_rows_*i + j] = _data_[_rows_*i + j];
      }
    }

    /* Create an identity Matrix elements array. */
    T * _data_new_ = new T[_rows_ * _rows_];
    for (i = 0; i < _rows_; i++) {
      for (j = 0; j < _rows_; j++) {
        _data_new_[_rows_*i + j] = i == j;
      }
    }

    /* decending escalate. */
    while (current_dim < _rows_ && det_0) {
      i = current_dim;

      /* find a row that have an element != 0 in the current column. */
      while (i < _rows_ && _data_res_[_rows_*i + current_dim] == 0) {
        i++;
      }

      /* if finded... */
      if (i != _rows_) {
        /* if not the same column, then change both. */
        if (current_dim < i) {
          for (j = 0; j < _rows_; j++) {
            std::swap(_data_res_[_rows_*i + j], _data_res_[_rows_*current_dim + j]);
            std::swap(_data_new_[_rows_*i + j], _data_new_[_rows_*current_dim + j]);
          }
        }

        /* do the rows multiplication. */
        cm_1 = onec / _data_res_[_rows_*current_dim + current_dim];
        for (i = current_dim+1; i < _rows_; i++) {
          cm_2 = _data_res_[_rows_*i + current_dim];
          if (cm_2 != 0) {
            cm_2 *= cm_1;
            for (j = current_dim; j < _columns_; j++) {
              _data_res_[_rows_*i + j] -= cm_2 * _data_res_[_rows_*current_dim + j];
            }
            for (j = 0; j < _columns_; j++) {
              _data_new_[_rows_*i + j] -= cm_2 * _data_new_[_rows_*current_dim + j];
            }
          }
        }
        current_dim++;
      } else {
        det_0 = false;
      }
    }

    /*
       rising escalate.
       */
    if (det_0) {
      current_dim--;
      while (current_dim >= 0) {
        cm_1 = onec / _data_res_[_rows_*current_dim + current_dim];
        for (i = current_dim-1; i >= 0; i--) {
          cm_2 = _data_res_[_rows_*i + current_dim] * cm_1;
          if (cm_2 != 0) {
            for (j = 0; j < _rows_; j++) {
              _data_new_[_rows_*i + j] -= cm_2 * _data_new_[_rows_*current_dim + j];
            }
          }
        }

        /* 
         * multiply the column by 1/cm_1 to make B(i,i) = 0 for all i 
         */
        for (j = 0; j < _rows_; j++) {
          _data_new_[_rows_ * current_dim + j] *= cm_1;
        }
        current_dim--;
      }
      ret = Matrix<T>(_rows_, _rows_, _data_new_, true);
    } else {
      delete [] _data_new_;
    }
    delete [] _data_res_;
  }
  return ret;
}
