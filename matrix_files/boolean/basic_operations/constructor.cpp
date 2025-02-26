#include "../../../matrix.hpp"

Matrix<bool>::Matrix (unsigned rows, unsigned columns, bool* data, bool consume_data) noexcept {
  _columns_ = columns;
  _rows_ = rows;
  _lenr_ = (rows + 7) >> 3;
  _lenc_ = (columns + 7) >> 3;
  rows = _lenr_ * _lenc_;
  _data_ = new uint64_t[rows];
  std::memset (_data_, 0, sizeof (uint64_t) * rows);

  uint64_t one = 1;
  for (int i = 0; i < _rows_; i++) {
    for (int j = 0; j < _columns_; j++) {
      if (data [i*_columns_ + j]) {
        _data_ [(i >> 3)*_lenc_ + (j >> 3)] |= one << ((i & 7) << 3) + (j & 7);
      }
    }
  }
  if (consume_data) delete [] data;
}
