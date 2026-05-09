#include "../../fix_matrix.hpp"

Matrix4 Matrix4::traspose () {
  __m128 tmp3, tmp2, tmp1, tmp0;
  tmp0 = _mm_unpacklo_ps(this->_data_[0]._v, this->_data_[1]._v);
  tmp2 = _mm_unpacklo_ps(this->_data_[2]._v, this->_data_[3]._v);
  tmp1 = _mm_unpackhi_ps(this->_data_[0]._v, this->_data_[1]._v);
  tmp3 = _mm_unpackhi_ps(this->_data_[2]._v, this->_data_[3]._v);

  this->_data_[0]._v = _mm_movelh_ps(tmp0, tmp2);
  this->_data_[1]._v = _mm_movehl_ps(tmp2, tmp0);
  this->_data_[2]._v = _mm_movelh_ps(tmp1, tmp3);
  this->_data_[3]._v = _mm_movehl_ps(tmp3, tmp1);

  return *this;
}
