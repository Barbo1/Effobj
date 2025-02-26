#include "../../../matrix.hpp"

template<arithmetric T>
bool Matrix<T>::is_square() const { return _columns_ == _rows_; }
