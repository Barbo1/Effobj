#include "../../../matrix.hpp"

Matrix<bool>::Matrix() noexcept {
  _data_ = nullptr;
  _columns_ = 0;
  _rows_ = 0;
  _lenr_ = 0;
  _lenc_ = 0;
}
