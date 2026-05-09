#include "../../../matrix.hpp"

Matrix<float>::~Matrix () {
  std::free (this->_data_);
}
