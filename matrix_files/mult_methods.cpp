
/* 
 *  Matrix by constant operator.
 **/
Matrix operator*(float multiplier) const {
    if(_rows_ != 0 && _columns_ != 0){
        T * _data_new_ = new T[_columns_*_rows_];
        for(unsigned i = 0; i < _rows_ * _columns_; i++) {
            _data_new_[i] = _data_[i] * multiplier;
        }
        return Matrix(_rows_, _columns_, _data_new_);
    }
    return Matrix();   
}

/* 
 *  Matrix by Matrix operator.
 **/
Matrix operator*(const Matrix & A) const {
    if(_columns_ == A._rows_) {
        unsigned i, j, k;
        unsigned res;
        T * _data_new_ = new T[_columns_*A._rows_];
        for(i = 0; i < _rows_; i++){
            for(j = 0; j < A._columns_; j++) {
                res = _rows_*i + j;
                _data_new_[res] = 0;
                for(k = 0; k < _columns_; k++) {
                    _data_new_[res] += _data_[_rows_*i + k] * A._data_[A._rows_*k + j];
                }
            }
        }
        return Matrix(_rows_, A._columns_, _data_new_);
    } else {
        return Matrix();
    }
}
