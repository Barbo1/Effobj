#include "../../../matrix.hpp"

bool Matrix<float>::is_stochastic () const { 
  unsigned i, j, pos;
  __m128 res;
  __m128 zeros = _mm_setzero_ps(), ones = _mm_set1_ps(1);
  fv_x4 accumulate;
  bool resul = true;

  i = 0;
  while(resul && i < _rows_) {
    j = 0;
    accumulate._v = _data_[_length_*i]._v;
    for(j = 1; j < _length_; j++) {
      res = _data_[_length_*i + j]._v;
      resul = !_mm_testc_ps (
        _mm_or_ps(
          _mm_cmp_ps(res, ones, 1), 
          _mm_cmp_ps(res, zeros, 14)
        ),
        _mm_set1_ps(0xffffffff)
      );
      accumulate._v = _mm_add_ps(res, accumulate._v);
    }
    resul = (accumulate._f[0] + accumulate._f[1] + accumulate._f[2] + accumulate._f[3]) == 1;
    i++;
  }
  return resul;
}
