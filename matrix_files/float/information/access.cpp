#include "../../../matrix.hpp"

float Matrix<float>::operator() (unsigned row, unsigned column) const {
  row--;
  column--;
  if(row <= _rows_ && column <= _columns_){
    return _data_[row*_length_ + column / 4]._f[column % 4];
  }
  return 0;
}
