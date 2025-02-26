#include "../../../matrix.hpp"

/*
 *  Return the determinant of the Matrix. If this is a null Matrix, 0 will be returned.
 * */
template <arithmetric T>
T Matrix<T>::determinant() {
  const T zeroc = 0;
  const T onec = 1;
  const T monec = -1;
  T determinant = onec;
  if(_rows_ != 0 && _columns_ != 0 && _columns_ == _rows_) {
    unsigned current_dim = 0, i, j;
    T cm_1, cm_2;

    /* Create a copy of the elements array converted to double. */
    T * _data_new_ = new T[_rows_ * _rows_];
    for (unsigned i = 0; i < _rows_ * _rows_; i++) {
      _data_new_[i] = _data_[i];
    }

    while(current_dim < _rows_ && determinant != zeroc) {
      i = current_dim;
      /* find a row that have an element != 0 in the current column. */
      while(i < _rows_ && _data_new_[_rows_*i + current_dim] == zeroc) {
        i++;
      }

      /* if finded... */
      if(i != _rows_) {
        /* if not the same column, then change both. */
        if(current_dim < i) {
          for(j = 0; j < _rows_; j++) {
            std::swap(_data_new_[_rows_*i + j], _data_new_[_rows_*current_dim + j]);
          }
          determinant *= monec;
        }
        /* do the rows multiplication. */
        cm_1 = _data_new_[_rows_*current_dim + current_dim];
        for(i = current_dim+1; i < _rows_; i++) {
          cm_2 = _data_new_[_rows_*i + current_dim] / cm_1;
          if(cm_2 != zeroc) {
            for(j = current_dim; j < _columns_; j++) {
              _data_new_[_rows_*i + j] -= cm_2*_data_new_[_rows_*current_dim + j];
            }
          }
        }
        current_dim++;
        determinant *= cm_1;
      } else {
        determinant = zeroc;
      }
    }
    delete [] _data_new_;
  }
  return determinant;
}    
