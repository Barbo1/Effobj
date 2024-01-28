
/*
 *  Change the rows referenced by 'row1' and 'row2'.
 * */
void changec(unsigned col1, unsigned col2) {
    col1--;
    col2--;
    if(col1 <= _columns_ && col2 <= _columns_ && col1 != col2) {  
        for(unsigned i = 0; i < _rows_; i++) {
            std::swap(_data_[_rows_*i + col1], _data_[_rows_*i + col2]);
        }
    }
}

/*
 *  Change the rows referenced by 'row1' and 'row2'.
 * */
void changer(unsigned row1, unsigned row2) {
    row1--;
    row2--;
    if(row1 <= _columns_ && row2 <= _columns_ && row1 != row2) {
        for(unsigned i = 0; i < _rows_; i++) {
            std::swap(_data_[_rows_*row1 + i], _data_[_rows_*row2 + i]);
        }
    }
}

/*
 *  Multiply the column referenced by 'column' by 'multiplier'.
 * */
void multr(unsigned row, float multiplier) {
    row--;
    if(row <= _rows_) { 
        for(unsigned i = _columns_ * row; i < _columns_ * (row + 1); i++) {
            _data_[i] *= multiplier;
        }
    }
}

/*
 *  Multiply the column referenced by 'column' by 'multiplier'.
 * */
void multc(unsigned column, float multiplier) { 
    column--;
    if(column <= _columns_) {
        for(unsigned i = 0; i < _rows_; i++) {
            _data_[_columns_*i + column] *= multiplier;
        }
    }
}
