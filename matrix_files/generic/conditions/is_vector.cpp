#include "../../../matrix.hpp"

template<arithmetric T>
bool Matrix<T>::is_vector() const { return _columns_ == 1 || _rows_ == 1; }
