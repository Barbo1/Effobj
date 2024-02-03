
/* 
 *  Addition operator.
 **/
Matrix operator+(const Matrix & M) const {
    if(_columns_ == M._columns_ && _rows_ == M._rows_) {
        unsigned i = _columns_*_rows_;
        T * _data_new_ = new T[i];
        memcpy (_data_new_, _data_, sizeof(T) * i);
        for (int i = 0; i < _columns_ * _rows_; i++) {
            _data_new_[i] += _data_[i];
        }
        return Matrix(_rows_, _columns_, _data_new_, true);
    } else {
        return Matrix();
    } 
}

