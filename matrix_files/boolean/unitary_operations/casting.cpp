#include "../../../matrix.hpp"

template<arithmetric U>
requires std::is_convertible_v <bool, U>
Matrix<U> Matrix<bool>::cast() {
  if(_rows_ != 0 && _columns_ != 0) {
    U * _data_new_ = new U[_rows_ * _columns_];
    uint64_t one = 1;
    for (int i = 0; i < _rows_; i++) {
      for (int j = 0; j < _columns_; j++) {
        _data_new_ [i * _columns_ + j] = 
          !!(_data_[(i >> 3) * _lenc_ + (j >> 3)] & one << ((i & 7) << 3) + (j & 7));
      }
    }
    return Matrix<U> (_rows_, _columns_, _data_new_, true);
  }
  return Matrix<U>();
}
