
/*
 *  Return the quantity of rows.  
 **/
unsigned rows() const { 
    return _rows_; 
}

/*
 *  Return the quantity of columns.  
 **/
unsigned cols() const {
    return _columns_;
}

/*
 *  Operator to access an element. Precondition: 1 <= row, column <= _rows_, _columns_
 * */
T& operator()(unsigned row, unsigned column) const {
    row--;
    column--;
    return _data_[_rows_*row + column];
}
