#include "../../../matrix.hpp"

template<arithmetric T>
Matrix<T>& Matrix<T>::operator=(const Matrix & M) {
  _rows_ = M._rows_;
  _columns_ = M._columns_;
  if(_rows_ != 0 && _columns_ != 0){
    if (_data_ != nullptr) {
      delete [] _data_;
    }
    _data_ = new T[_rows_ * _columns_];
    for (int i = 0; i < _columns_ * _rows_; i++) {
      _data_ [i] = M._data_[i];
    }
  } else {
    _data_ = nullptr;
  }
  return *this;
}
