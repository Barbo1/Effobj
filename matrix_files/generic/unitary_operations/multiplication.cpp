#include "../../../matrix.hpp"

/* 
 *  Matrix by constant operator.
 **/
template <arithmetric T>
Matrix<T> Matrix<T>::operator*(T multiplier) const {
  if (_rows_ != 0 && _columns_ != 0){
    T * _data_new_ = new T[_columns_ * _rows_];
    for (unsigned i = 0; i < _rows_ * _columns_; i++) {
      _data_new_[i] = _data_[i] * multiplier;
    }
    return Matrix(_rows_, _columns_, _data_new_, true);
  }
  return Matrix();   
}
