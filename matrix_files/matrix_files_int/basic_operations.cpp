
/* Creation of a null matrix. 
 * */
Matrix () {
    this->_data_ = nullptr;
    this->_rows_ = 0;
    this->_columns_ = 0;
}

/* Generic constructor. 
 * */
template<typename U>
requires std::convertible_to<U, T*>
Matrix (unsigned rows, unsigned columns, const U data, bool consume_data = false) {
    _rows_ = rows;
    _columns_ = columns;
    if (consume_data) {
        _data_ = data;
    } else {
        _data_ = new T[columns * rows];
        for (int i = 0; i < rows * columns; i++) {
            _data_ [i] = data [i];
        }
    }
}

Matrix (const Matrix & M) {
    _rows_ = M._rows_;
    _columns_ = M._columns_;
    if(_rows_ != 0 && _columns_ != 0) {
        _data_ = new T[_rows_ * _columns_];
        std::memcpy (_data_, M._data_, sizeof (T) * _columns_ * _rows_);
    } else {
        _data_ = nullptr;
    }
}

Matrix(Matrix && M) noexcept {
    _data_ = std::exchange(M._data_, nullptr);
    _rows_ = std::exchange(M._rows_, 0);
    _columns_ = std::exchange(M._columns_, 0);
}

Matrix& operator=(const Matrix & M) {
    _rows_ = M._rows_;
    _columns_ = M._columns_;
    if(_rows_ != 0 && _columns_ != 0){
        if (_data_ != nullptr) {
            delete [] _data_;
        }
        _data_ = new T[_rows_ * _columns_];
        std::memcpy (_data_, M._data_, sizeof (T) * _columns_ * _rows_);
    } else {
        _data_ = nullptr;
    }
    return *this;
}

Matrix& operator=(Matrix && M) noexcept {
    if (_data_ != nullptr) {
        delete [] _data_;
    }
    _data_ = std::exchange(M._data_, nullptr);
    _rows_ = std::exchange(M._rows_, 0);
    _columns_ = std::exchange(M._columns_, 0);
    return *this;
}

~Matrix(){
    if(_data_ != nullptr){
        delete [] _data_;
    }
}

