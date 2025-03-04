#include "../../fix_matrix_d.hpp"
#include <iostream>

float Matrix4::determinant () { 
  return (
    (this->_data_[0]._f[3] * this->_data_[2]._f[2] - this->_data_[0]._f[2] * this->_data_[2]._f[3]) *
    (this->_data_[1]._f[0] * this->_data_[3]._f[1] - this->_data_[3]._f[0] * this->_data_[1]._f[1])
  ) + (
    (this->_data_[0]._f[3] * this->_data_[2]._f[0] - this->_data_[0]._f[0] * this->_data_[2]._f[3]) *
    (this->_data_[1]._f[1] * this->_data_[3]._f[2] - this->_data_[3]._f[1] * this->_data_[1]._f[2])
  ) + (
    (this->_data_[0]._f[1] * this->_data_[2]._f[0] - this->_data_[0]._f[0] * this->_data_[2]._f[1]) *
    (this->_data_[1]._f[2] * this->_data_[3]._f[3] - this->_data_[1]._f[3] * this->_data_[3]._f[2])
  ) + (
    (this->_data_[0]._f[2] * this->_data_[2]._f[0] - this->_data_[0]._f[0] * this->_data_[2]._f[2]) *
    (this->_data_[1]._f[3] * this->_data_[3]._f[1] - this->_data_[1]._f[1] * this->_data_[3]._f[3])
  ) + (
    (this->_data_[0]._f[1] * this->_data_[2]._f[3] - this->_data_[0]._f[3] * this->_data_[2]._f[1]) *
    (this->_data_[1]._f[0] * this->_data_[3]._f[2] - this->_data_[3]._f[0] * this->_data_[1]._f[2])
  ) + (
    (this->_data_[0]._f[2] * this->_data_[2]._f[1] - this->_data_[0]._f[1] * this->_data_[2]._f[2]) *
    (this->_data_[1]._f[0] * this->_data_[3]._f[3] - this->_data_[3]._f[0] * this->_data_[1]._f[3])
  );
}
