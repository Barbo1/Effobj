#include "../../../matrix.hpp"

Matrix<float> Matrix<float>::attached(unsigned row_to_elim, unsigned col_to_elim) {
  row_to_elim--;
  col_to_elim--;
  if (row_to_elim <= _rows_ && col_to_elim <= _columns_) {
    unsigned res_1, res_2, res_3;
    unsigned _rows_new_ = _rows_-1, _columns_new_ = _columns_-1;
    unsigned length_new = (_columns_new_ + 3) / 4;
    fv_x4 * _data_new_ = new fv_x4[_rows_new_ * length_new];
    for (unsigned i = 0; i < _rows_; i++) {
      res_1 = length_new * (i - (i > row_to_elim));
      res_2 = _length_*i;
      for (unsigned j = 0; j < _columns_; j++) {
        if (i != row_to_elim && j != col_to_elim) {
          res_3 = (j - (j > col_to_elim));
          _data_new_[res_1 + res_3 / 4]._f[res_3 % 4] = 
            _data_[res_2 + j / 4]._f[j % 4];
        }
      }
    }
    return Matrix(_rows_new_, _columns_new_, _data_new_);
  } else {
    return Matrix();
  }
}
