#include "../../../matrix.hpp"
#include <cstdint>

Matrix<float> Matrix<float>::operator* (const Matrix & A) const {
  if (_columns_ == A._rows_) {
    fv_x4 * _data_new_ = static_cast<fv_x4*>(
      std::aligned_alloc(16, sizeof(fv_x4) * _length_ * _rows_)
    );

    for (uint64_t r = 0; r < this->_rows_; r++) {

      // first step.
      float current_elem = this->_data_[r * this->_length_]._f[0];
      __m128 curr_elem_v = _mm_set1_ps(current_elem);
      for (uint64_t i = 0; i < A._length_; i++) {
        _mm_stream_ps(
          (float*)(_data_new_ + r * A._length_ + i), 
          _mm_mul_ps(curr_elem_v, A._data_[i]._v)
        );
      }

      // following steps.
      for (uint64_t c = 1; c < this->_columns_; c++) {
        current_elem = this->_data_[r * this->_length_ + (c >> 2)]._f[c & 3];
        curr_elem_v = _mm_set1_ps(current_elem);
        for (uint64_t i = 0; i < A._length_; i++) {
          float* _data_new_pos_ = (float*)(_data_new_ + r * A._length_ + i);
          _mm_store_ps(
            _data_new_pos_, 
            _mm_fmadd_ps(
              curr_elem_v, 
              _mm_load_ps((float*)(A._data_ + c * A._length_ + i)),
              _mm_load_ps(_data_new_pos_)
            )
          );
        }
      } 
    }

    return Matrix(_rows_, A._columns_, _data_new_);
  } else {
    return Matrix();
  }
}

Matrix<float> Matrix<float>::operator*= (const Matrix & A) const {
  if (_columns_ == A._rows_ && A._rows_ == A._columns_) {
    fv_x4 * _data_new_ = static_cast<fv_x4*>(
      std::aligned_alloc(16, sizeof(fv_x4) * _length_ * _rows_)
    );

    for (uint64_t r = 0; r < this->_rows_; r++) {

      // first step.
      float current_elem = this->_data_[r * this->_length_]._f[0];
      __m128 curr_elem_v = _mm_set1_ps(current_elem);
      for (uint64_t i = 0; i < A._length_; i++) {
        _mm_stream_ps(
          (float*)(_data_new_ + r * A._length_ + i), 
          _mm_mul_ps(curr_elem_v, A._data_[i]._v)
        );
      }

      // following steps.
      for (uint64_t c = 1; c < this->_columns_; c++) {
        current_elem = this->_data_[r * this->_length_ + (c >> 2)]._f[c & 3];
        curr_elem_v = _mm_set1_ps(current_elem);
        for (uint64_t i = 0; i < A._length_; i++) {
          float* _data_new_pos_ = (float*)(_data_new_ + r * A._length_ + i);
          _mm_store_ps(
            _data_new_pos_, 
            _mm_fmadd_ps(
              curr_elem_v, 
              _mm_load_ps((float*)(A._data_ + c * A._length_ + i)),
              _mm_load_ps(_data_new_pos_)
            )
          );
        }
      } 
    }

    for (uint32_t i = 0; i < this->_rows_; i++) {
      for (uint32_t j = 0; j < this->_columns_; j++) {
        this->_data_[i*this->_columns_ + j]._v = _data_new_[i*this->_columns_ + j]._v;
      }
    }
  }
  return *this;
}
