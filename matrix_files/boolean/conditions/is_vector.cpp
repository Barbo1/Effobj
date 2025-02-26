#include "../../../matrix.hpp"

bool Matrix<bool>::is_vector () const {
  return _columns_ == 1 || _rows_ == 1;
}
