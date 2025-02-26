#include "../../../matrix.hpp"

template<arithmetric T>
Matrix<T>::Matrix(Matrix && M) noexcept {
  _data_ = std::exchange(M._data_, nullptr);
  _rows_ = std::exchange(M._rows_, 0);
  _columns_ = std::exchange(M._columns_, 0);
}
