#include "../../../matrix.hpp"

Matrix<bool>::Matrix(Matrix && M) noexcept {
  _data_ = std::exchange(M._data_, nullptr);
  _rows_ = std::exchange(M._rows_, 0);
  _columns_ = std::exchange(M._columns_, 0);
  _lenr_ = std::exchange(M._lenr_, 0);
  _lenc_ = std::exchange(M._lenc_, 0);
}
