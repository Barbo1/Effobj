
/* 
 *  Addition operator.
 **/
Matrix operator+(const Matrix & M) const {
    if(_columns_ == M._columns_ && _rows_ == M._rows_) {
        unsigned i;
        T * _data_new_ = new T[_columns_*_rows_];
        for(i = 0; i < _rows_ * _columns_; i++) {
            _data_new_[i] = _data_[i] + M._data_[i];
        }
        return Matrix(_rows_, _columns_, _data_new_);
    } else {
        return Matrix();
    } 
}

