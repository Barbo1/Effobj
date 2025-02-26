#include "../../../matrix.hpp"

template<arithmetric T>
Matrix<T>::~Matrix(){
  if(_data_ != nullptr){
    delete [] _data_;
  }
}
