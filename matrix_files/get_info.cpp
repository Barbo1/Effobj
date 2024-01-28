
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
 *  Operator to access an element.
 * */
float operator()(unsigned row, unsigned column) const {
    row--;
    column--;
    if(row <= _rows_ && column <= _columns_) {
        return _data_[_rows_*row + column];
    }
    return 0;
}
