#include "../../../matrix.hpp"

template<arithmetric U>
requires (!std::is_same_v<U, float>)
Matrix<U> Matrix<float>::cast () {
  if(_rows_ != 0 && _columns_ != 0) {
    unsigned length = _rows_ * _length_;
    U * _data_new_ = new U[length];
    for(signed char i = 0; i < _rows_; i++) {
      for(signed char j = 0; j < _columns_; j++){
        _data_new_[i*_columns_ + j] = (U)_data_[(i*length + j) / 4]._f[j % 4];
      }
    }
    return Matrix<U>(_rows_, _columns_, _data_new_);
  } else {
    return Matrix<U>();
  }
}
