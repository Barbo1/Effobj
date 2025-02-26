#include "../../../matrix.hpp"

Matrix<float> Matrix<float>::invert() {
  Matrix ret = Matrix();
  if(_rows_ != 0 && _columns_ != 0 && _columns_ == _rows_) {
    int current_dim = 0, i, j;
    float cm_1, cm_2;
    unsigned * res_1 = new unsigned[4];
    bool det_0 = true;
    fv_x4 * _data_new_, * _iden_;
    __m128 res = _mm_setzero_ps();

    i = _rows_ * _length_;
    _data_new_= new fv_x4[i];
    _iden_ = new fv_x4[i];
    for(i = 0; i < _rows_ * _length_; i++) {
      _data_new_[i] = _data_[i];
      _iden_[i]._v = res;
    }
    for(i = 0; i < _rows_; i++){
      _iden_[_length_*i + i/4]._f[i % 4] = 1;
    }

    while(current_dim < _rows_ && det_0) {
      i = current_dim;
      res_1[0] = current_dim / 4;
      res_1[1] = current_dim % 4;
      res_1[2] = _length_*current_dim;

      while(i < _rows_ && _data_new_[_length_*i + res_1[0]]._f[res_1[1]] == 0) {
        i++;
      }

      if(i != _rows_) {
        if(current_dim < i) {
          res_1[4] = _length_*i;
          for(j = 0; j < _length_; j++) {
            std::swap(_data_new_[res_1[4] + j]._v, _data_new_[res_1[2] + j]._v);
            std::swap(_iden_[res_1[4] + j]._v, _iden_[res_1[2] + j]._v);
          }
        }
        cm_1 = _data_new_[res_1[2] + res_1[0]]._f[res_1[1]];
        for(i = (current_dim+1) * _length_; i < _rows_*_length_; i += _length_) {
          cm_2 = _data_new_[i + res_1[0]]._f[res_1[1]] / cm_1;
          if(cm_2 != 0) {
            res = _mm_set1_ps(cm_2);
            for(j = res_1[0]; j < _length_; j++) {
              _data_new_[i + j]._v = _mm_fnmadd_ps(res, 
                  _data_new_[res_1[2] + j]._v, 
                  _data_new_[i + j]._v);
            }
            for(j = 0; j < _length_; j++) {
              _iden_[i + j]._v = _mm_fnmadd_ps(
                  res,
                  _iden_[res_1[2] + j]._v,
                  _iden_[i + j]._v);
            }
          }
        }
        current_dim++;
      } else {
        det_0 = false;
      }
    }

    if(det_0) {
      current_dim--;
      for(; current_dim >= 0; current_dim--) {
        res_1[0] = current_dim / 4;
        res_1[1] = current_dim % 4;
        res_1[2] = _length_*current_dim;
        cm_1 = 1 / _data_new_[res_1[2] + res_1[0]]._f[res_1[1]];
        for(i = (current_dim-1) * _length_; i >= 0; i -= _length_) {
          cm_2 = _data_new_[i + res_1[0]]._f[res_1[1]];
          if(cm_2 != 0) {
            res = _mm_set1_ps(cm_2 * cm_1);
            for(j = 0; j < _length_; j++) {
              _iden_[i + j]._v = _mm_fnmadd_ps(res, 
                  _iden_[res_1[2] + j]._v,
                  _iden_[i + j]._v);
            }
          }
        }
        res = _mm_set1_ps(cm_1);
        for(j = res_1[2]; j < res_1[2] + _length_; j++) {
          _iden_[j]._v = _mm_mul_ps(_iden_[j]._v, res);
        }
      }
      ret = Matrix(_rows_, _rows_, _iden_);
    } else {
      delete [] _iden_;
    }
    delete [] res_1;
    delete [] _data_new_;
  }
  return ret;
}
