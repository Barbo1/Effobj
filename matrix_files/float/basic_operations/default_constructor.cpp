#include "../../../matrix.hpp"

Matrix<float>::Matrix () noexcept {
  _data_ = nullptr;
  _length_ = 0;
  _rows_ = 0;
  _columns_ = 0;
}
