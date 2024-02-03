
/*
 *  floatest if the matrix is a null matrix.
 * */
bool is_null() const {
    return _rows_ == 0 || _columns_ == 0;
}

/*
 *  floatest if the matrix is a square matrix.
 **/
bool is_square() const {
    return _columns_ == _rows_;
}

/* Test if the martix is a vector.
 * */
bool is_vector() const {
    return _columns_ == 1 || _rows_ == 1;
}

/* Test if the matrix is stochastic(the sum of the elements in all rows is 1, and all elements
 * are between 0 and 1).
 * */
bool is_stochastic() const { 
    unsigned i = 0, j;
    T accumulate;
    bool resul = false;

    while(resul && i < _columns_) {
        j = 0;
        accumulate = 0;
        while(resul && j < _rows_) {
            if (0 > _data_[_rows_*i + j] || _data_[_rows_*i + j] > 1) goto fin;
            accumulate += _data_[_rows_*i + j++];
        }
        if (accumulate != 1) goto fin;
        i++;
    }
    resul = true;
    fin:
    return resul;
}
