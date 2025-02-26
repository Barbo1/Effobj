#include "../../fix_matrix_d.hpp"

bool Matrix4::is_null() const {
  return _data_ == nullptr;
}
