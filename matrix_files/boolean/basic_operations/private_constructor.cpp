#include "../../../matrix.hpp"

Matrix<bool>::Matrix (unsigned rows, unsigned columns, uint64_t * data) {
  _columns_ = columns;
  _rows_ = rows;
  _data_ = data;
  _lenr_ = (rows + 7) >> 3;
  _lenc_ = (columns + 7) >> 3;
}
