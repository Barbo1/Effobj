#include "../../../matrix.hpp"

bool Matrix<bool>::is_null () const {
  return !_rows_ || !_columns_;
}
