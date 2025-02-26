#include "../../../matrix.hpp"

template<arithmetric T>
Matrix<T>& Matrix<T>::operator=(Matrix && M) noexcept {
  if (_data_ != nullptr) {
    delete [] _data_;
  }
  _data_ = std::exchange(M._data_, nullptr);
  _rows_ = std::exchange(M._rows_, 0);
  _columns_ = std::exchange(M._columns_, 0);
  return *this;
}
