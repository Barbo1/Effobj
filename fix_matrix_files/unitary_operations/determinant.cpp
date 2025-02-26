#include "../../fix_matrix_d.hpp"

float Matrix4::determinant () { 
  fv_x4 * _data_new_ = new fv_x4[4];
  __m128 zero = _mm_setzero_ps();
  float determinant = 1;
  float cm_1, cm_2;

  _data_new_[0]._v = _data_[0]._v;
  _data_new_[1]._v = _data_[1]._v;
  _data_new_[2]._v = _data_[2]._v;
  _data_new_[3]._v = _data_[3]._v;

  /*--------------iteration-1----------------*/

  if (_data_new_[0]._f[0] == 0) {
    if (_data_new_[1]._f[0] != 0) {
      std::swap(_data_new_[1]._v, _data_new_[0]._v);
      determinant *= -1;
    } else if (_data_[2]._f[0] != 0) {
      std::swap(_data_new_[2]._v, _data_new_[0]._v);
      determinant *= -1;
    } else if (_data_new_[3]._f[0] != 0) {
      std::swap(_data_new_[3]._v, _data_new_[0]._v);
      determinant *= -1;
    } else {
      delete [] _data_new_;
      return 0;
    }
  }

  cm_1 = 1/_data_new_[0]._f[0];
  if ((cm_2 = _data_new_[1]._f[0]) != 0) {
    cm_2 *= cm_1;
    _data_new_[1]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _data_new_[0]._v, _data_new_[1]._v);
  }
  if ((cm_2 = _data_new_[2]._f[0]) != 0) {
    cm_2 *= cm_1;
    _data_new_[2]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _data_new_[0]._v, _data_new_[2]._v);
  }
  if ((cm_2 = _data_new_[3]._f[0]) != 0) {
    cm_2 *= cm_1;
    _data_new_[3]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _data_new_[0]._v, _data_new_[3]._v);
  }

  determinant *= _data_new_[0]._f[0];

  /*--------------iteration-2----------------*/

  if (_data_new_[1]._f[1] == 0) {
    if (_data_new_[2]._f[1] != 0) {
      std::swap(_data_new_[2]._v, _data_new_[1]._v);
      determinant *= -1;
    } else if (_data_[3]._f[1] != 0) {
      std::swap(_data_new_[3]._v, _data_new_[1]._v);
      determinant *= -1;
    } else {
      delete [] _data_new_;
      return 0;
    }
  }

  cm_1 = 1/_data_new_[1]._f[1];
  if ((cm_2 = _data_new_[2]._f[1]) != 0) {
    cm_2 *= cm_1;
    _data_new_[2]._v = _mm_fnmadd_ps (
      _mm_set1_ps(cm_2), 
      _data_new_[1]._v, 
      _data_new_[2]._v
    );
  }
  if ((cm_2 = _data_new_[3]._f[1]) != 0) {
    cm_2 *= cm_1;
    _data_new_[3]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _data_new_[1]._v, _data_new_[3]._v);
  }

  determinant *= _data_new_[1]._f[1];

  /*--------------iteration-3----------------*/

  if (_data_new_[2]._f[2] == 0) {
    if (_data_new_[3]._f[2] != 0) {
      std::swap(_data_new_[3]._v, _data_new_[2]._v);
      determinant *= -1;
    } else {
      delete [] _data_new_;
      return 0;
    }
  }

  cm_1 = _data_new_[2]._f[2];
  if ((cm_2 = _data_new_[3]._f[2]) != 0) {
    cm_2 /= cm_1;
    _data_new_[3]._v = _mm_fnmadd_ps (
      _mm_set1_ps(cm_2), 
      _data_new_[2]._v, 
      _data_new_[3]._v
    );
  }

  determinant *= cm_1;

  /*------------------------------*/

  determinant *= _data_new_[3]._f[3];
  delete [] _data_new_;
  return determinant;
}
