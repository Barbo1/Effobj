#include "../../../matrix.hpp"

Matrix<float>::Matrix (unsigned rows, unsigned columns, fv_x4 * data, bool consume) noexcept {
  _rows_ = rows;
  _columns_ = columns;
  _length_ = (columns + 3) / 4;
  _data_ = data;
}
