#include "../../../matrix.hpp"

bool Matrix<bool>::is_square () const {
  return _columns_ == _rows_;
}
