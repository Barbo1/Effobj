#include "../../../matrix.hpp"

void Matrix<float>::multr(unsigned row, float multiplier) {
  row--;
  if (row <= _rows_) { 
    __m128 res = _mm_set1_ps(multiplier);
    for  (unsigned i = _length_ * row; i < _length_ * (row + 1); i++) {
      _data_[i]._v = _mm_mul_ps(_data_[i]._v, res);
    }
  }
}
