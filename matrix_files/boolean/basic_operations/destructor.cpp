#include "../../../matrix.hpp"

Matrix<bool>::~Matrix () {
  if(_data_ != nullptr){
    delete [] _data_;
  }
}
