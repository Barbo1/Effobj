#include "../../../matrix.hpp"

void Matrix<bool>::multiply_by_index (
    int i, 
    int j, 
    int rows, 
    int _lenc_, 
    int index,
    uint64_t * _data_, 
    uint64_t * _A_data_, 
    uint64_t * _data_new_ 
    ) {
  static int64_t data_val, res, one = 1;
  _data_new_ [index] = 0;
  for (int ki = i * _lenc_, kj = j, k = 0; k < _lenc_; k++, ki++, kj += _lenc_) {
    data_val = 0;
    for (int r = 0, rs = 0; r < rows; r++, rs = r << 3) {
      res = 0;
      for (int c = 0; c < 8; c++) {
        if (_data_ [ki] & one << rs + c) {
          res |= Matrix::rvm [c];
        }
      }
      res &= _A_data_ [kj];
      res |= (18446744069414584320ULL & res) >> 32;
      res |= (4294901760ULL & res) >> 16;
      res |= (65280ULL & res) >> 8;
      data_val |= (255ULL & res) << rs;
    }
    _data_new_ [index] |= data_val;
  }
}
