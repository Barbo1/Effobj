#include "../../../matrix.hpp"

template<arithmetric T>
template<arithmetric U>
requires std::is_convertible_v<T, U>
Matrix<U> Matrix<T>::cast() const {
  if (_rows_ != 0 && _columns_ != 0) {
    U * _data_new_ = new U[_rows_ * _columns_];
    for (unsigned i = 0; i < _rows_ * _columns_; i++) {
      _data_new_[i] = (U)_data_[i];
    }
    return Matrix<U>(_rows_, _columns_, _data_new_, true);
  } else {
    return Matrix<U>();
  }
}
