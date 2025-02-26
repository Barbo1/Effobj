#include "../../../matrix.hpp"

Matrix<bool> Matrix<bool>::attached (unsigned row, unsigned col) {
  row--;
  col--;
  if (row < _rows_ && col < _columns_) {
    uint64_t lenr = (_rows_ + 6) >> 3;
    uint64_t lenc = (_columns_ + 6) >> 3;
    uint64_t * _data_new_ = new uint64_t[lenr * lenc];
    uint64_t maskr = rvm_sum[(row & 7) + 1];
    uint64_t maskc = cvm_sum[(col & 7) + 1];
    uint64_t maskrf = ~rvm_sum[row & 7];
    uint64_t maskcf = ~cvm_sum[col & 7];
    col = col >> 3;
    row = row >> 3;

    /* copying the "static" part. */
    for (int i = 0; i < lenr; i++) {
      for (int j = i*_lenc_, k = i*lenc; k < (i + 1)*lenc; j++, k++) {
        _data_new_[k] = _data_[j];
      }
    }

    /* shifting columns. */
    int j, k;
    for (int i = 0; i < lenr; i++) {
      j = i * _lenc_ + col;
      k = i * lenc + col;

      if (k < lenc * lenr) {

        /* first iteration. */
        _data_new_ [k] = maskcf & _data_new_[k] | (maskc & _data_new_[k]) >> 1;
        j++;
        k++;

        /* middle iterations. */
        for (; k < (i + 1) * lenc - 1; j++, k++) {
          _data_new_ [k-1] |= _data_new_[k] << 7;
          _data_new_ [k] = _data_new_[k] >> 1 ;
        }

        /*
         * es posible cambiar la condicion del if por: 
         *    lenc < _lenc_ + 1
         *
         * y la variable j calcularla directamente mediante: 
         *    j = i * _lenc_ + lenc - 1
         * */

        /* last iteration. */
        if (j < (i + 1) * _lenc_) {
          uint64_t res = _data_[j];
          _data_new_ [k-1] |= res << 7;
          if (lenr == _lenr_) {
            _data_new_ [k] = res >> 1;
          }
        }
      }
    }

    /* shifting rows. */
    for (int i = 0; i < lenc; i++) {
      j = _lenc_ * row + i;
      k = lenc * row + i;

      if (k < lenc * lenr) {

        /* first iteration. */
        _data_new_ [k] = maskrf & _data_new_[k] | (maskr & _data_new_[k]) >> 8;
        j += _lenc_; 
        k += lenc;

        /* middle iterations. */
        for (; k < lenc * (lenr - 1); j += _lenc_, k += lenc) {
          _data_new_ [k-lenc] |= _data_new_ [k] << 56;
          _data_new_ [k] = _data_new_ [k] >> 8;
        }

        /*
         * k = lenc * row + i + lenc
         * j = _lenc_ * row + i + _lenc_ + _lenc_ * (lenc * (lenr - row - 2) - i) / lenc
         *
         * i = 0 -> j = i + _lenc_ * (lenr - 1)
         * i > 0 -> j = i + _lenc_ * (lenr - 2)
         *
         * -> j = i + _lenc_ * (lenr - 1 - (i > 0))
         *  i + _lenc_ * (i > 0) < _lenc_ * (_lenr_ - lenr - 1)
         *
         *
         * es posible cambiar la condicion del if por: 
         *    i + _lenc_ * (i > 0) < _lenc_ * (_lenr_ - lenr - 1) 
         *
         * y la variable j calcularla directamente mediante: 
         *    j = i + _lenc_ * (lenr - 1 - (i > 0))
         * */

        /* last iteration. */
        if (j < _lenc_ * _lenr_) {
          _data_new_ [k-lenc] |= _data_[j] << 56;
          if (lenc == _lenc_) {
            _data_new_ [k] = _data_[j] >> 8;
          }
        }
      }
    }

    return Matrix(_rows_ - 1, _columns_ - 1, _data_new_);
  }
  return Matrix();
}
