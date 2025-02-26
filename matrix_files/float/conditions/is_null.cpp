#include "../../../matrix.hpp"

bool Matrix<float>::is_null () const {
  return _rows_ == 0 || _columns_ == 0;
}
