
template<arithmetric T>
/*
 * Return an identity matrix with the dimention passed by parameter.
 */
Matrix<T> identity(unsigned dimension) {
    if(dimension != 0){
        unsigned i, j;
        T * _data_new_ = new T[dimension * dimension];
        for(i = 0; i < dimension; i++) {
            for(j = 0; j < dimension; j++) {
                _data_new_[dimension*i + j] = i == j;
            }
        }
        return Matrix<T>(dimension, dimension, _data_new_);
    } else {
        return Matrix<T>();
    }
}

template<arithmetric T>
Matrix<T> mfo(unsigned row, unsigned col, T elem) {
    if(row != 0 && col != 0) {
        unsigned i, j;
        T * _data_new_;
        _data_new_ = new T[row*col];
        for(i = 0; i < row; i++) {
            for(j = 0; j < col; j++) {
                _data_new_[row*i + j] = elem;
            }
        }
        return Matrix<T>(row, col, _data_new_);
    } else {
        return Matrix<T>();
    } 
}

