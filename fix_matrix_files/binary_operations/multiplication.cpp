#include "../../fix_matrix.hpp"

Matrix4 Matrix4::operator* (const Matrix4& A) {
  for (int i = 0; i < 4; i++) {
    __m128 res1 = _mm_fmadd_ps (
      _mm_set1_ps (this->_data_[i]._f[0]), A._data_[0]._v, 
      _mm_mul_ps (_mm_set1_ps (this->_data_[i]._f[1]), A._data_[1]._v) 
    );
    __m128 res2 = _mm_fmadd_ps (
      _mm_set1_ps (this->_data_[i]._f[2]), A._data_[2]._v, 
      _mm_mul_ps (_mm_set1_ps (this->_data_[i]._f[3]), A._data_[3]._v) 
    );

    this->_data_[i]._v = _mm_add_ps (res1, res2);
  }

  return *this;
}
