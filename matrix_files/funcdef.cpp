
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
        return Matrix<T>(dimension, dimension, _data_new_, true);
    } else {
        return Matrix<T>();
    }
}

template<arithmetric T>
Matrix<T> mfo(unsigned row, unsigned col, T elem) {
    if(row != 0 && col != 0) {
        unsigned i, j;
        T * _data_new_ = new T[row * col];
        for(i = 0; i < row*col; i++) {
            _data_new_[i] = elem;
        }
        return Matrix<T>(row, col, _data_new_, true);
    } else {
        return Matrix<T>();
    } 
}

