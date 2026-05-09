#include "../../fix_matrix.hpp"

Matrix4::Matrix4 () {
  _data_[0]._v = _mm_setzero_ps();
  _data_[1]._v = _mm_setzero_ps();
  _data_[2]._v = _mm_setzero_ps();
  _data_[3]._v = _mm_setzero_ps();
}
