#include "../../../matrix.hpp"

template<arithmetric T>
Matrix<T>::Matrix () {
  _data_ = nullptr;
  _rows_ = 0;
  _columns_ = 0;
}
