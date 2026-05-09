#include "../../../matrix.hpp"
#include <cstdint>

bool Matrix<float>::is_stochastic () const { 
  __m128 res, accumulation;
  bool resul = true;

  uint64_t i = 0, mask, pos = 0;
  while (resul && i < this->_rows_) {
    accumulation = res = this->_data_[pos++]._v;
    mask = _mm_movemask_epi8(_mm_castps_si128(res));
    resul &= !(mask & 0x8888);

    for (unsigned j = 1; j < this->_length_; j++) {
      res = this->_data_[pos++]._v;
      accumulation = _mm_add_ps(res, accumulation);
      mask = _mm_movemask_epi8(_mm_castps_si128(res));
      resul &= !(mask & 0x8888);
    }

    accumulation = _mm_hadd_ps(accumulation, accumulation);
    accumulation = _mm_hadd_ps(accumulation, accumulation);
    float acc = _mm_cvtss_f32(accumulation);

    resul &= 0.9998f < acc && acc < 1.0001f;
    i++;
  }
  return resul;
}
