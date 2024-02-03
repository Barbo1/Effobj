double determinant() {
    double determinant = 1;
    if(_rows_ != 0 && _columns_ != 0 && _columns_ == _rows_) {
        unsigned current_dim = 0, i, j;
        double cm_1, cm_2;

        /* Create a copy of the elements array converted to double. */
        double * _data_double_ = new double[_rows_ * _rows_];
        for(i = 0; i < _rows_; i++) {
            for(j = 0; j < _rows_; j++) {
                _data_double_[_rows_*i + j] = _data_[_rows_*i + j];
            }
        }

        while(current_dim < _rows_ && determinant != 0) {
            i = current_dim;
            /* 
             * find a row that have an element != 0 in the current column. 
             */
            while(i < _rows_ && _data_double_[_rows_*i + current_dim] == 0) {
                i++;
            }

            /* if finded... */
            if(i != _rows_) {
                /* if not the same column, then change both. */
                if(current_dim < i) {
                    for(j = 0; j < _rows_; j++) {
                        std::swap(_data_double_[_rows_*i + j], 
                                _data_double_[_rows_*current_dim + j]);
                    }
                    determinant *= -1;
                }
                /* do the rows multiplication. */
                cm_1 = _data_double_[_rows_*current_dim + current_dim];
                for(i = current_dim+1; i < _rows_; i++) {
                    cm_2 = _data_double_[_rows_*i + current_dim] / cm_1;
                    if(cm_2 != 0) {
                        for(j = current_dim; j < _columns_; j++) {
                            _data_double_[_rows_*i + j] -= cm_2*_data_double_[_rows_*current_dim + j];
                        }
                    }
                }
                current_dim++;
                determinant *= cm_1;
            } else {
                determinant = 0;
            }
        }
        delete [] _data_double_;
    }
    return determinant;
}
