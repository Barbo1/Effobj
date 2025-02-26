#include "../../../matrix.hpp"

Matrix<bool>::Matrix (unsigned rows, unsigned columns) noexcept {
  _columns_ = columns;
  _rows_ = rows;
  _lenr_ = (rows + 7) >> 3;
  _lenc_ = (columns + 7) >> 3;
  _data_ = new uint64_t[_lenr_ * _lenc_];
  std::memset (_data_, 0, sizeof (uint64_t) * _lenr_ * _lenc_);
}
