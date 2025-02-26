#include "../../fix_matrix_d.hpp"

Matrix4 Matrix4::invert () {
  fv_x4 * _data_new_ = new fv_x4[4];
  fv_x4 * _iden_ = new fv_x4[4];
  __m128 zero = _mm_setzero_ps(), res;
  float cm_1, cm_2;

  _data_new_[0]._v = _data_[0]._v;
  _data_new_[1]._v = _data_[1]._v;
  _data_new_[2]._v = _data_[2]._v;
  _data_new_[3]._v = _data_[3]._v;

  _iden_[0]._v = _iden_[1]._v = _iden_[2]._v = _iden_[3]._v = zero;
  _iden_[0]._f[0] = _iden_[1]._f[1] = _iden_[2]._f[2] = _iden_[3]._f[3] = 1;

  /*--------------iteration-1----------------*/

  if (_data_new_[0]._f[0] == 0) {
    if (_data_new_[1]._f[0] != 0) {
      std::swap(_data_new_[1]._v, _data_new_[0]._v);
      std::swap(_iden_[1]._v, _iden_[0]._v);
    } else if (_data_new_[2]._f[0] != 0) {
      std::swap(_data_new_[2]._v, _data_new_[0]._v);
      std::swap(_iden_[2]._v, _iden_[0]._v);
    } else if (_data_new_[3]._f[0] != 0) {
      std::swap(_data_new_[3]._v, _data_new_[0]._v);
      std::swap(_iden_[3]._v, _iden_[0]._v);
    } else {
      delete [] _data_new_;
      delete [] _iden_;
      return Matrix4();
    }
  }

  cm_1 = 1/_data_new_[0]._f[0];

  if ((cm_2 = _data_new_[1]._f[0]) != 0) {
    cm_2 *= cm_1;
    res = _mm_set1_ps(cm_2);
    _data_new_[1]._v = _mm_fnmadd_ps(res, _data_new_[0]._v, _data_new_[1]._v);
    _iden_[1]._v = _mm_fnmadd_ps(res, _iden_[0]._v, _iden_[1]._v);
  }
  if ((cm_2 = _data_new_[2]._f[0]) != 0) {
    cm_2 *= cm_1;
    res = _mm_set1_ps(cm_2);
    _data_new_[2]._v = _mm_fnmadd_ps(res, _data_new_[0]._v, _data_new_[2]._v);
    _iden_[2]._v = _mm_fnmadd_ps(res, _iden_[0]._v, _iden_[2]._v);
  }
  if ((cm_2 = _data_new_[3]._f[0]) != 0) {
    cm_2 *= cm_1;
    res = _mm_set1_ps(cm_2);
    _data_new_[3]._v = _mm_fnmadd_ps(res, _data_new_[0]._v, _data_new_[3]._v);
    _iden_[3]._v = _mm_fnmadd_ps(res, _iden_[0]._v, _iden_[3]._v);
  }

  /*--------------iteration-2----------------*/

  if (_data_new_[1]._f[1] == 0) {
    if (_data_new_[2]._f[1] != 0) {
      std::swap(_data_new_[2]._v, _data_new_[1]._v);
      std::swap(_iden_[2]._v, _iden_[1]._v);
    } else if (_data_new_[3]._f[1] != 0) {
      std::swap(_data_new_[3]._v, _data_new_[1]._v);
      std::swap(_iden_[3]._v, _iden_[1]._v);
    } else {
      delete [] _data_new_;
      delete [] _iden_;
      return Matrix4();
    }
  }

  cm_1 = 1/_data_new_[1]._f[1];

  if ((cm_2 = _data_new_[2]._f[1]) != 0) {
    cm_2 *= cm_1;
    res = _mm_set1_ps(cm_2);
    _data_new_[2]._v = _mm_fnmadd_ps(res, _data_new_[1]._v, _data_new_[2]._v);
    _iden_[2]._v = _mm_fnmadd_ps(res, _iden_[1]._v, _iden_[2]._v);
  }
  if ((cm_2 = _data_new_[3]._f[1]) != 0) {
    cm_2 *= cm_1;
    res = _mm_set1_ps(cm_2);
    _data_new_[3]._v = _mm_fnmadd_ps(res, _data_new_[1]._v, _data_new_[3]._v);
    _iden_[3]._v = _mm_fnmadd_ps(res, _iden_[1]._v, _iden_[3]._v);
  }

  /*--------------iteration-3----------------*/

  if(_data_new_[2]._f[2] == 0) {
    if(_data_new_[3]._f[2] != 0) {
      std::swap(_data_new_[3]._v, _data_new_[2]._v);
      std::swap(_iden_[3]._v, _iden_[2]._v);
    } else {
      delete [] _data_new_;
      delete [] _iden_;
      return Matrix4();
    }
  }

  cm_1 = 1/_data_new_[2]._f[2];

  if ((cm_2 = _data_new_[3]._f[2]) != 0) {
    cm_2 *= cm_1;
    res = _mm_set1_ps(cm_2);
    _data_new_[3]._v = _mm_fnmadd_ps(res, _data_new_[2]._v, _data_new_[3]._v);
    _iden_[3]._v = _mm_fnmadd_ps(res, _iden_[2]._v, _iden_[3]._v);
  }

  /*--------------iteration-4---------------*/

  if (_data_new_[3]._f[3] == 0) {
    delete [] _data_new_;
    delete [] _iden_;
    return Matrix4();
  } 

  /*---------------reverse-iteration-1--------------*/

  cm_1 = 1/_data_new_[3]._f[3];
  res = _mm_set1_ps(cm_1);
  _iden_[3]._v = _mm_mul_ps(res, _iden_[3]._v);

  if ((cm_2 = _data_new_[2]._f[3]) != 0) {
    _iden_[2]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _iden_[3]._v, _iden_[2]._v);
  }
  if ((cm_2 = _data_new_[1]._f[3]) != 0) {
    _iden_[1]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _iden_[3]._v, _iden_[1]._v);
  }
  if ((cm_2 = _data_new_[0]._f[3]) != 0) {
    _iden_[0]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _iden_[3]._v, _iden_[0]._v);
  }

  /*---------------reverse-iteration-2--------------*/

  cm_1 = 1/_data_new_[2]._f[2]; 
  res = _mm_set1_ps(cm_1);
  _iden_[2]._v = _mm_mul_ps(res, _iden_[2]._v);

  if ((cm_2 = _data_new_[1]._f[2]) != 0) {
    _iden_[1]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _iden_[2]._v, _iden_[1]._v);
  }
  if ((cm_2 = _data_new_[0]._f[2]) != 0) {
    _iden_[0]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _iden_[2]._v, _iden_[0]._v);
  }

  /*---------------reverse-iteration-3--------------*/

  cm_1 = 1/_data_new_[1]._f[1];
  _iden_[1]._v = _mm_mul_ps(_mm_set1_ps(cm_1), _iden_[1]._v);

  if ((cm_2 = _data_new_[0]._f[1]) != 0) {
    _iden_[0]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _iden_[1]._v, _iden_[0]._v);
  }

  /*---------------reverse-iteration-4--------------*/

  _iden_[0]._v = _mm_mul_ps(_mm_set1_ps(1/_data_new_[0]._f[0]), _iden_[0]._v);

  /*---------------return--------------*/

  delete [] _data_new_;
  return Matrix4(_iden_);
}
