#include "../../../matrix.hpp"

Matrix<float> Matrix<float>::operator+(const Matrix & M) const {
  if(_columns_ == M._columns_ && _rows_ == M._rows_) {
    fv_x4 * _data_new_ = static_cast<fv_x4*>(
      std::aligned_alloc(16, sizeof(fv_x4) * _length_ * _rows_)
    );

    for(unsigned i = 0; i < _rows_ * _length_; i++)
      _mm_stream_ps((float*)(_data_new_ + i), _mm_add_ps(M._data_[i]._v, _data_[i]._v));

    return Matrix(_rows_, _columns_, _data_new_);
  } else {
    return Matrix();
  } 
}
