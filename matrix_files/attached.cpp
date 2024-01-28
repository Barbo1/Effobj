
/*
 *  Return the attached matrix in the coordinates passed by parameter. If the coordinates exceed
 *  the matrix range an null matrix will be returned.
 * */
Matrix attached(unsigned row_to_elim, unsigned col_to_elim) {
    row_to_elim--;
    col_to_elim--;
    if(row_to_elim <= _rows_ && col_to_elim <= _columns_) {
        unsigned i, j, pos_i, pos_j;
        unsigned _rows_new_ = _rows_-1, _columns_new_ = _columns_-1;
        T * _data_new_ = new T[_rows_new_*_columns_new_];
        for(i = 0; i < _rows_; i++) {
            for(j = 0; j < _columns_; j++) {
                pos_i = i;
                if(i > row_to_elim) {
                    pos_i--;
                }
                pos_j = j;
                if(j > col_to_elim) {
                    pos_j--;
                }
                if(i != row_to_elim && j != col_to_elim) {
                    _data_new_[_rows_new_*pos_i + pos_j] = _data_[_rows_*i + j];
                }
            }
        }
        return Matrix(_rows_new_, _columns_new_, _data_new_);
    } else {
        return Matrix();
    }
}
