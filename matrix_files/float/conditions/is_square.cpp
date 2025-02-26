#include "../../../matrix.hpp"

bool Matrix<float>::is_square () const {
  return _columns_ == _rows_;
}
