#include "../../../matrix.hpp"
#include <cstdint>

Matrix<float> Matrix<float>::operator*(float multiplier) const {
  if(_rows_ != 0 && _columns_ != 0){
    fv_x4 * _data_new_ = static_cast<fv_x4*>(
      std::aligned_alloc(16, sizeof(fv_x4) * _length_ * _rows_)
    );
    __m128 res = _mm_set1_ps(multiplier);
    for(uint32_t j = 0; j < _rows_ * _length_; j++) {
      _data_new_[j]._v = _mm_mul_ps(_data_[j]._v, res);
    }
    return Matrix(_rows_, _columns_, _data_new_);
  }
  return Matrix();   
}

Matrix<float> Matrix<float>::operator*=(float multiplier) const {
  if(_rows_ != 0 && _columns_ != 0){
    __m128 res = _mm_set1_ps(multiplier);
    for(uint32_t j = 0; j < _rows_ * _length_; j++) {
      _data_[j]._v = _mm_mul_ps(_data_[j]._v, res);
    }
  }
  return *this; 
}
