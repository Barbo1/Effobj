
/*
 *  floatest if the matrix is a null matrix.
 * */
bool is_null() {
    return _rows_ == 0 || _columns_ == 0;
}

/*
 *  floatest if the matrix is a square matrix.
 **/
bool is_square() const {
    return _columns_ == _rows_;
}

/*
 *  floatest if the martix is a vector.
 * */
bool is_vector() const {
    return _columns_ == 1 || _rows_ == 1;
}

/*
 *  floatest if the matrix is stochastic(the sum of the elements in all rows is 1, and all elements
 *  are between 0 and 1).
 * */
bool is_stochastic() const { 
    unsigned i = 0, j;
    T accumulate;
    bool resul = true;

    while(resul && i < _columns_) {
        j = 0;
        accumulate = 0;
        while(resul && j < _rows_) {
            if(0 <= _data_[_rows_*i + j] && _data_[_rows_*i + j] <= 1){
                accumulate += _data_[_rows_*i + j];
            } else {
                resul = false;
            }
            j++;
        }
        if(accumulate != 1) 
            resul = false;
        i++;
    }
    return resul;
}
