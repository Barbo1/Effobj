#include "../../../matrix.hpp"

template<arithmetric T>
template<typename U>
requires std::convertible_to<U, T*>
Matrix<T>::Matrix (unsigned rows, unsigned columns, const U data, bool consume_data) {
  this->_rows_ = rows;
  this->_columns_ = columns;
  if (consume_data) {
    this->_data_ = data;
  } else {
    this->_data_ = new T[columns*rows];
    for (unsigned i = 0; i < rows * columns; i++) {
      this->_data_ [i] = data [i];
    }
  }
}
