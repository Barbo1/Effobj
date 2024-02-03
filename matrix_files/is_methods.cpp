
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
