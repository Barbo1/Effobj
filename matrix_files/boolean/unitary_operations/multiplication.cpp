#include "../../../matrix.hpp"

Matrix<bool> Matrix<bool>::operator*(bool multiplier) const {
  if(_rows_ != 0 && _columns_ != 0){ 
    uint64_t * _data_new_;
    if (multiplier) {
      _data_new_ = new uint64_t[_lenc_ * _lenr_];
      memcpy (_data_new_, _data_, sizeof(uint64_t) * _lenc_ * _lenr_);
    } else {
      _data_new_ = new uint64_t[_lenc_ * _lenr_] {0};
    }
    return Matrix(_rows_, _columns_, _data_new_);
  }
  return Matrix();
}
