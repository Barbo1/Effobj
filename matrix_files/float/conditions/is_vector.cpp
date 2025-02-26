#include "../../../matrix.hpp"

bool Matrix<float>::is_vector() const {
  return _columns_ != 0 && _rows_ != 0 && (_columns_ == 1 ^ _rows_ == 1);
}
