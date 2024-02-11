/*********************************
 *    Generic Size, Bool type    *
 *********************************/

typedef vectorBM uint32_t;
const int bitsVectorBM = 32;

template<>
class Matrix<bool>{
private:
    /* Probar bitset que se puede hacer con el otro modelo. */
    vectorBM * _data_;
    unsigned _rows_;
    unsigned _columns_;
public:
    Matrix() {
       _data_ = nullptr;
       _columns_ = 0;
       _rows_ = 0;
    }

    template<typename U>
    requires std::is_same_v< U, bool* >
    Matrix (unsigned rows, unsigned columns, U data, bool consume_data = false) {
        int _len_buck_ = columns / bitsVectorBM;
        _columns_ = columns;
        _rows_ = rows;
        _data_ = new vectorBM[_len_buck_ * _rows_]{0};
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                _data_[i*_len_buck_ + j / bitsVectorBM] |= data[i*columns + j] << ((bitsVectorBM ^ 1) - j % bitsVectorBM);
            }
        }
        if (consume_data) delete [] data;
    }

    Matrix(const Matrix & M) {
        _rows_ = M._rows_;
        _columns_ = M._columns_;
        if(_rows_ != 0 && _columns_ != 0) {
            int length = _rows_ * (_columns_ / bitsVectorBM);
            _data_ = new vectorBM[length];
            for(int i = 0; i < length; i++) {
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
            unsigned length = _rows_ * (_columns_ / bitsVectorBM);
            _data_ = new vectorBM[length];
            for(int i = 0; i < length; i++){
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
        _rows_ = std::exchange (M._rows_, 0);
        _columns_ = std::exchange (M._columns_, 0);
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
    requires std::is_convertible_v <bool, U>
    Matrix<U> cast() {
        if(_rows_ != 0 && _columns_ != 0) {
            unsigned length = _rows_ * _columns_;
            U * _data_new_ = new U[length];
            for (unsigned i = 0; i < _rows_; i++) {
                for (unsigned j = 0; j < _columns_; j++) {
                    _data_new_ [i * _columns_ + j] = 
                        _data_[i * _len_buck_ + j / bitsVectorBM] & 
                        (1 << ((bitsVectorBM ^ 1) - j % bitsVectorBM));
                }
            }
            return Matrix<U>(_rows_, _columns_, _data_new_, true);
        }
        return Matrix<U>();
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
    void changec (unsigned col1, unsigned col2) {
        col1--;
        col2--;
        if (col1 <= _columns_ && col2 <= _columns_ && col1 != col2) {
            vectorBM mask1 = col1 % bitsVectorBM;
            vectorBM mask2 = col2 % bitsVectorBM;
            if (mask1 > mask2) {
                std::swap (mask1, mask2);
                std::swap (col1, col2);
            }
            int k = mask2 - mask1;
            mask1 = 1 << (bitsVectorBM - 1 - mask1);
            mask2 = 1 << (bitsVectorBM - 1 - mask2);
            col1 /= bitsVectorBM;
            col2 /= bitsVectorBM;
            int _len_ = _columns_ / bitsVectorBM;

            if (col2 == col1) {
                for (int i = col1; i < _rows_ * _len_ + col1; i += _len_) {
                    vectorBM & t = _data_[i];
                    t = (t & ~(mask1 | mask2)) | ((t & mask2) << k) | ((t >> k) & mask2);
                }
            } else {
                vectorBM r;
                for (int i = 0; i < _rows_ * _len_; i += _len_) {
                    vectorBM& t1 = _data_[i + col1];
                    vectorBM& t2 = _data_[i + col2];
                    r = (t1 & mask1) >> k;
                    t1 = (t1 & ~mask1) | ((t2 & mask2) << k);
                    t2 = (t2 & ~mask2) | r;
                }
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
            int _len_ =  _columns_ / bitsVectorBM;
            for(int i = 0; i < _len_; i++) {
                std::swap(_data_[_len_ * row1 + i], _data_[_len_ * row2 + i]);
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
        if (row <= _rows_ && column <= _columns_) {
            return 
                _data_[(_columns_ / bitsVectorBM) * row + column / bitsVectorBM] & 
                (1 << (bitsVectorBM - 1 - column % bitsVectorBM);
        }
        return 0;
    }
 
    /*
     *  Return the transpose of the matrix. If this is a null matrix, the resulting also will be.
     **/
    /* Falta */
    Matrix traspose() {
        if (_columns_ != 0 && _rows_ != 0) {
            int _len_ = _rows_ / bitsVectorBM;
            vectorBM * _data_new_ = new vectorBM[_columns_ * _len_];
            for (int i = 0; i < _len_; i++) {
                for (int j = 0; j < _columns_; j++) {
                    _data_new_[_rows_*i + j] = _data_[_rows_*j + i];
                }
            }
            return Matrix(_columns_, _rows_, _data_new_, true);
        } else {
            return Matrix();
        }
    }
    
    /*
     *  Return the attached matrix in the coordinates passed by parameter. If the coordinates exceed
     *  the matrix range an null matrix will be returned.
     * */
    /* Falta */
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
            return Matrix(_rows_new_, _columns_new_, _data_new_, true);
        } else {
            return Matrix();
        }
    }

    /*
     *  Multiply the column referenced by 'column' by 'multiplier'.
     * */
    void multr(unsigned row, bool multiplier) {
        row--;
        if (row <= _rows_ && !mutiplier) {
            int _len_ = _columns_ / bitsVector;
            for (unsigned i = _len_ * row; i < _len_ * (row + 1); i++) {
                _data_[i] = 0;
            }
        }
    }
    
    /*
     *  Multiply the column referenced by 'column' by 'multiplier'.
     * */
    void multc(unsigned column, bool multiplier) { 
        column--;
        if(column <= _columns_ && !multiplier) {
            int _len_ = _columns_ / bitsVectorBM;
            int mask = ~(1 << (bitsVectorBM - 1 - column % bitsVectorBM));
            for (int i = 0; i < _rows_; i++) {
                _data_[_columns_*i + column] &= mask;
            }
        }
    }

    /* 
     *  Matrix by Matrix operator.
     **/
    /* Falta */
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
            return Matrix(_rows_, A._columns_, _data_new_, true);
        }
        return Matrix();
    }

    /* 
     *  Matrix by constant operator.
     **/
    Matrix<bool> operator*(bool multiplier) const {
        if(_rows_ != 0 && _columns_ != 0){ 
            int len = (_columns_ / bitsVectorBM)*_rows_;
            vectorBM * _data_new_;
            if (multiplier) {
                _data_new_ = new vectorBM[len];
                memcpy (_data_new_, _data_, sizeof(vectorBM) * len);
            } else {
                _data_new_ = new vectorBM[len]{0};
            }
            return Matrix(_rows_, _columns_, _data_new_, true);
        }
        return Matrix();
    }

    /* 
     *  Addition operator.
     **/
    Matrix operator+(const Matrix & M) const {
        if(_columns_ == M._columns_ && _rows_ == M._rows_) {
            int _len_ = _columns_ / bitsVectorBM;
            vectorBM * _data_new_ = new vectorBM[_len_ * _rows_];
            for (int i = 0; i < _len_ * _rows_; i++) {
                _data_new_[i] = _data_[i] | M._data_[i];
            }
            return Matrix(_rows_, _columns_, _data_new_, true);
        } 
        return Matrix();
    } 
};
