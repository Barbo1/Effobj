/*********************************
 *    Generic Size, Bool type    *
 *********************************/

template<>
class Matrix<bool>{
private:
    bool * _data_;
    unsigned _rows_;
    unsigned _columns_;
public:
    Matrix() {
       _data_ = nullptr;
       _rows_ = 0;
       _columns_ = 0;
    }

    template<typename U>
    requires std::is_same_v< std::remove_reference_t<U>, bool* >
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
            unsigned length = _rows_ * _columns_;
            unsigned i;
            _data_ = new bool[length];
            for(unsigned i = 0; i < length; i++) {
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
            unsigned length = _rows_ * _columns_;
            unsigned i;
            if (_data_ != nullptr) {
                delete [] _data_;
            }
            _data_ = new bool[length];
            for(unsigned i = 0; i < length; i++){
                _data_[i] = M._data_[i];
            }
        } else {
            _data_ = nullptr;
        }
        return *this;
    }

    Matrix operator=(Matrix && M) noexcept {
        delete [] _data_;
        _data_ = std::exchange(M._data_, nullptr);
        _rows_ = M._rows_;
        _columns_ = M._columns_;
        return *this;
    }

    ~Matrix(){
        if(_data_ != nullptr){
            delete [] _data_;
        }
    }

    /*
     *  Return a matrix resulting of cast the elements from the actual type to the specified.
     * */
    template<arithmetric U>
    Matrix<U> cast() {
        if(_rows_ != 0 && _columns_ != 0) {
            unsigned length = _rows_ * _columns_;
            U * _data_new_ = new U[length];
            for(unsigned i = 0; i < length; i++) {
                _data_new_[i] = (U)_data_[i];
            }
            return Matrix<U>(_rows_, _columns_, _data_new_);
        } else {
            return Matrix<U>();
        }
    }

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
     *  floatest if the matrix is a null matrix.
     * */
    bool is_null() {
        return _rows_ == 0 || _columns_ == 0;
    }

    /*
     *  floatest if the matrix is a square matrix.
     **/
    bool is_square() const {
        return _columns_ == _rows_;
    }

    /*
     *  floatest if the martix is a vector.
     * */
    bool is_vector() const {
        return _columns_ == 1 || _rows_ == 1;
    }
      
    /*
     *  Operator to access an element.
     * */
    bool operator()(unsigned row, unsigned column) const {
        row--;
        column--;
        if(row <= _rows_ && column <= _columns_){
            return _data_[_rows_*row + column];
        }
        return 0;
    }
 
    /*
     *  Return the transpose of the matrix. If this is a null matrix, the resulting also will be.
     **/
    Matrix traspose() {
        if(_columns_ != 0 && _rows_ != 0) {
            unsigned i, j;
            bool * _data_new_ = new bool[_columns_*_rows_];
            for(i = 0; i < _rows_; i++) {
                for(j = 0; j < _columns_; j++) {
                    _data_new_[_rows_*i + j] = _data_[_rows_*j + i];
                }
            }
            return Matrix(_columns_, _rows_, _data_new_);
        } else {
            return Matrix();
        }
    }
    
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
            bool * _data_new_ = new bool[_rows_new_*_columns_new_];
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

    /*
     *  Multiply the column referenced by 'column' by 'multiplier'.
     * */
    void multr(unsigned row, bool multiplier) {
        row--;
        if(row <= _rows_) {
            for(unsigned i = _columns_ * row; i < _columns_ * (row + 1); i++) {
                _data_[i] &= multiplier;
            }
        }
    }
    
    /*
     *  Multiply the column referenced by 'column' by 'multiplier'.
     * */
    void multc(unsigned column, bool multiplier) { 
        column--;
        if(column <= _columns_) {
            for(unsigned i = 0; i < _rows_; i++) {
                _data_[_columns_*i + column] &= multiplier;
            }
        }
    }

    /* 
     *  Matrix by constant operator.
     **/
    Matrix<bool> operator*(bool multiplier) const {
        if(_rows_ != 0 && _columns_ != 0){ 
            bool * _data_new_ = new bool[_columns_*_rows_];
            if (multiplier) {
                for(unsigned i = 0; i < _rows_ * _columns_; i++) {
                    _data_new_[i] = _data_[i];
                }
            } else {
                for(unsigned i = 0; i < _rows_ * _columns_; i++) {
                    _data_new_[i] = false;
                }
            }
            return Matrix(_rows_, _columns_, _data_new_);
        }
        return Matrix();
    }

    /* 
     *  Matrix by Matrix operator.
     **/
    Matrix operator*(const Matrix & A) const {
        if (_columns_ == A._rows_) {
            unsigned i, j, k;
            unsigned res;
            bool * _data_new_ = new bool[_columns_*A._rows_];
            for (i = 0; i < _rows_; i++) {
                for (j = 0; j < A._columns_; j++) {
                    res = _rows_*i + j;
                    _data_new_[res] = false;
                    k = 0;
                    while (!_data_new_[res] && k < _columns_) {
                        _data_new_[res] = _data_[_rows_*i + k] && A._data_[A._rows_*k + j];
                        k++;
                    }
                }
            }
            return Matrix(_rows_, A._columns_, _data_new_);
        } else {
            return Matrix();
        }
    }

    /* 
     *  Addition operator.
     **/
    Matrix operator+(const Matrix & M) const {
        if(_columns_ == M._columns_ && _rows_ == M._rows_) {
            unsigned i;
            bool * _data_new_ = new bool[_columns_*_rows_];
            for(i = 0; i < _rows_ * _columns_; i++) {    
                _data_new_[i] = _data_[i] || M._data_[i];
            }
            return Matrix(_rows_, _columns_, _data_new_);
        } else {
            return Matrix();
        } 
    } 
};
