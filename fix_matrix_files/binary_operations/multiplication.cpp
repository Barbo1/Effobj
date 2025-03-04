#include "../../fix_matrix_d.hpp"

Matrix4 Matrix4::operator* (const Matrix4 & A) {
  fv_x4 * _data_new_  = new fv_x4[4];
  __m128 res1, res2;

  for (int i = 0; i < 4; i++) {
    res1 = _mm_add_ps (
      _mm_mul_ps (_mm_set1_ps (this->_data_[i]._f[0]), A._data_[0]._v), 
      _mm_mul_ps (_mm_set1_ps (this->_data_[i]._f[1]), A._data_[1]._v) 
    );
    res2 = _mm_add_ps (
      _mm_mul_ps (_mm_set1_ps (this->_data_[i]._f[2]), A._data_[2]._v), 
      _mm_mul_ps (_mm_set1_ps (this->_data_[i]._f[3]), A._data_[3]._v) 
    );

    _data_new_ [i]._v = _mm_add_ps (res1, res2);
  }

  return Matrix4 (_data_new_);
}
