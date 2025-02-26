#include "../../../matrix.hpp"

template<arithmetric T>
bool Matrix<T>::is_null() const { return _rows_ == 0 || _columns_ == 0; }
