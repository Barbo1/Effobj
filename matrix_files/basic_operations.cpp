
Matrix() {
    _data_ = nullptr;
    _rows_ = 0;
    _columns_ = 0;
}

template<typename U>
requires std::is_same_v< std::remove_reference_t<U>, T* >
Matrix(unsigned rows, unsigned columns, U && data){
    _rows_ = rows;
    _columns_ = columns;
    _data_ = data;
    if(std::is_lvalue_reference_v<U>) {
        data = nullptr;
    }
}

Matrix(const Matrix & M) {
    _rows_ = M._rows_;
    _columns_ = M._columns_;
    if(_rows_ != 0 && _columns_ != 0) {
        _data_ = new T[_rows_ * _columns_];
        for(unsigned i = 0; i < _rows_ * _columns_; i++) {
            _data_[i] = M._data_[i];
        }
    } else {
        _data_ = nullptr;
    }
}

Matrix(Matrix && M) noexcept {
    _data_ = std::exchange(M._data_, nullptr);
    _rows_ = std::exchange(M._rows_, 0);
    _columns_ = std::exchange(M._columns_, 0);
}

Matrix operator=(const Matrix & M) {
    _rows_ = M._rows_;
    _columns_ = M._columns_;
    if(_rows_ != 0 && _columns_ != 0){
        if (_data_ != nullptr) {
            delete [] _data_;
        }
        _data_ = new T[_rows_ * _columns_];
        for(unsigned i = 0; i < _rows_ * _columns_; i++){
            _data_[i] = M._data_[i];
        }
    } else {
        _data_ = nullptr;
    }
    return *this;
}

Matrix operator=(Matrix && M) noexcept {
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

