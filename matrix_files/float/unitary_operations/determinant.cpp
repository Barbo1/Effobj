#include "../../../matrix.hpp"

float Matrix<float>::determinant() {
  float determinant;
  if (_rows_ != 0 && _columns_ != 0 && _columns_ == _rows_) {
    unsigned current_dim = 0, i, j;
    float cm_1, cm_2;
    unsigned * res_1 = new unsigned[3];
    fv_x4 * _data_new_;
    __m128 res;

    determinant = 1;
    _data_new_= new fv_x4[_rows_ * _length_];
    for (i = 0; i < _rows_ * _length_; i++) {
      _data_new_[i]._v = _data_[i]._v;
    }

    while (determinant != 0 && current_dim < _rows_) {
      i = current_dim;
      res_1[0] = current_dim / 4;
      res_1[1] = current_dim % 4;
      res_1[2] = current_dim * _length_;
      while (i < _rows_ && _data_new_[_length_*i + res_1[0]]._f[res_1[1]] == 0) {
        i++;
      }

      if (i != _rows_) {
        if (current_dim < i) {
          for (j = 0; j < _length_; j++) {
            std::swap(_data_new_[_length_*i + j]._v, _data_new_[res_1[2] + j]._v);
          }
          determinant *= -1;
        }
        cm_1 = _data_new_[res_1[2] + res_1[0]]._f[res_1[1]];
        for (i = current_dim+1; i < _rows_; i++) {
          cm_2 = _data_new_[_length_*i + res_1[0]]._f[res_1[1]];
          if (cm_2 != 0) {
            res = _mm_set1_ps(cm_2 / cm_1);
            for (j = current_dim/4; j < _length_; j++) {
              _data_new_[_length_*i + j]._v = 
                _mm_fnmadd_ps(res, 
                    _data_new_[res_1[2] + j]._v,
                    _data_new_[_length_*i + j]._v
                    );
            }
          }
        }
        current_dim++;
        determinant *= cm_1;
      } else {
        determinant = 0;
      }
    }
    delete [] res_1;
    delete [] _data_new_;
  } else {
    determinant = 0;
  }
  return determinant;
} 
