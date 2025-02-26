#include "../../../matrix.hpp"

Matrix<float> Matrix<float>::operator*(float multiplier) const {
  if(_rows_ != 0 && _columns_ != 0){
    unsigned j;
    unsigned length = _rows_ * _length_;
    fv_x4 * _data_new_ = new fv_x4[length];
    __m128 res = _mm_set1_ps(multiplier);
    for(j = 0; j < length; j++) {
      _data_new_[j]._v = _mm_mul_ps(_data_[j]._v, res);
    }
    return Matrix(_rows_, _columns_, _data_new_);
  }
  return Matrix();   
}
