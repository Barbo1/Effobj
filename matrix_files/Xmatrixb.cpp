#include "../matrix.hpp"

/*********************************
 *    Generic Size, Bool type    *
 *********************************/

template<>
class Matrix<bool>{
private:
    uint64_t * _data_;
    int _lenr_;
    int _lenc_;
    int _rows_;
    int _columns_;

    /* vectors of masks. */
    static constexpr uint64_t tvm[14] {
        72057594037927936ULL, 144396663052566528ULL, 288794425616760832ULL, 577588855528488960ULL, 
        1155177711073755136ULL, 2310355422147575808ULL, 4620710844295151872ULL, 36099303471055874ULL, 
        141012904183812ULL, 550831656968ULL, 2151686160ULL, 8405024ULL, 32832ULL, 128ULL
    };

    static constexpr uint64_t cvm[8] {
        72340172838076673ULL, 144680345676153346ULL, 289360691352306692ULL, 578721382704613384ULL, 
        1157442765409226768ULL, 2314885530818453536ULL, 4629771061636907072ULL, 9259542123273814144ULL
    };

    static constexpr uint64_t rvm[8] {
        255ULL, 65280ULL, 16711680ULL, 4278190080ULL, 1095216660480ULL, 280375465082880ULL, 
        71776119061217280ULL, 18374686479671623680ULL
    };
    
    /* Constructor to not allocate so much memory. */
    Matrix (unsigned rows, unsigned columns, uint64_t * data) {
        _columns_ = columns;
        _rows_ = rows;
        _data_ = data;
        _lenr_ = (rows + 7) >> 3;
        _lenc_ = (columns + 7) >> 3;
    }

    /* Method needed to make the multiplication. */
    static void multiply_by_index (
            int i, int j, int rows, int _lenc_, int index,
            uint64_t * _data_, uint64_t * _A_data_, uint64_t * _data_new_ 
        ) {
        static int64_t data_val, res, one = 1;
        _data_new_ [index] = 0;
        for (int ki = i * _lenc_, kj = j, k = 0; k < _lenc_; k++, ki++, kj += _lenc_) {
            data_val = 0;
            for (int r = 0, rs = 0; r < rows; r++, rs = r << 3) {
                res = 0;
                for (int c = 0; c < 8; c++) {
                    if (_data_ [ki] & one << rs + c) {
                        res |= Matrix::rvm [c];
                    }
                }
                res &= _A_data_ [kj];
                res |= (18446744069414584320ULL & res) >> 32;
                res |= (4294901760ULL & res) >> 16;
                res |= (65280ULL & res) >> 8;
                data_val |= (255ULL & res) << rs;
            }
            _data_new_ [index] |= data_val;
        }
    }

public:
    
    /****************************
     *     Basic operations     *
     ****************************/

    Matrix() {
        _data_ = nullptr;
        _columns_ = 0;
        _rows_ = 0;
        _lenr_ = 0;
        _lenc_ = 0;
    }
    
    Matrix (unsigned rows, unsigned columns, bool* data, bool consume_data = false) {
        _columns_ = columns;
        _rows_ = rows;
        _lenr_ = (rows + 7) >> 3;
        _lenc_ = (columns + 7) >> 3;
        rows = _lenr_ * _lenc_;
        _data_ = new uint64_t[rows];
        std::memset (_data_, 0, sizeof (uint64_t) * rows);

        uint64_t one = 1;
        for (int i = 0; i < _rows_; i++) {
            for (int j = 0; j < _columns_; j++) {
                if (data [i*_columns_ + j]) {
                    _data_ [(i >> 3)*_lenc_ + (j >> 3)] |= one << ((i & 7) << 3) + (j & 7);
                }
            }
        }
        if (consume_data) delete [] data;
    }

    Matrix (unsigned rows, unsigned columns) {
        _columns_ = columns;
        _rows_ = rows;
        _lenr_ = (rows + 7) >> 3;
        _lenc_ = (columns + 7) >> 3;
        _data_ = new uint64_t[_lenr_ * _lenc_];
        std::memset (_data_, 0, sizeof (uint64_t) * _lenr_ * _lenc_);
    }

    Matrix(const Matrix & M) {
        _rows_ = M._rows_;
        _columns_ = M._columns_;
        _lenr_ = M._lenr_;
        _lenc_ = M._lenc_;
        int top = _lenr_ * _lenc_;
        if (top != 0) {
            _data_ = new uint64_t[top];
            std::memcpy (_data_, M._data_, sizeof(uint64_t) * top);
        } else {
            _data_ = nullptr;
        }
    }
   
    Matrix(Matrix && M) noexcept {
        _data_ = std::exchange(M._data_, nullptr);
        _rows_ = std::exchange(M._rows_, 0);
        _columns_ = std::exchange(M._columns_, 0);
        _lenr_ = std::exchange(M._lenr_, 0);
        _lenc_ = std::exchange(M._lenc_, 0);
    }

    Matrix operator=(const Matrix & M) {
        _rows_ = M._rows_;
        _columns_ = M._columns_;
        _lenr_ = M._lenr_;
        _lenc_ = M._lenc_;
        int top = _lenr_ * _lenc_;
        if (top != 0){
            if (_data_ != nullptr) {
                delete [] _data_;
            }
            _data_ = new uint64_t[top];
            std::memcpy (_data_, M._data_, sizeof(uint64_t) * top);
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
        _lenr_ = std::exchange(M._lenr_, 0);
        _lenc_ = std::exchange(M._lenc_, 0);

        return *this;
    }

    ~Matrix(){
        if(_data_ != nullptr){
            delete [] _data_;
        }
    }

    /* Return a matrix resulting of cast the elements from the actual type to the specified.
     * */
    template<arithmetric U>
    requires std::is_convertible_v <bool, U>
    Matrix<U> cast() {
        if(_rows_ != 0 && _columns_ != 0) {
            U * _data_new_ = new U[_rows_ * _columns_];
            uint64_t one = 1;
            for (int i = 0; i < _rows_; i++) {
                for (int j = 0; j < _columns_; j++) {
                    _data_new_ [i * _columns_ + j] = 
                        !!(_data_[(i >> 3) * _lenc_ + (j >> 3)] & one << ((i & 7) << 3) + (j & 7));
                }
            }
            return Matrix<U> (_rows_, _columns_, _data_new_, true);
        }
        return Matrix<U>();
    }



    /*************************************
     *     Return info of the matrix     *
     *************************************/
    
    /* Return the quantity of rows.  
     * */
    unsigned rows() const {
        return _rows_;
    }

    /* Return the quantity of columns.  
     * */
    unsigned cols() const {
        return _columns_;
    }
    
    /* Test if the matrix is a null matrix.
     * */
    bool is_null() {
        return !_rows_ || !_columns_;
    }

    /* Test if the matrix is a square matrix.
     * */
    bool is_square() const {
        return _columns_ == _rows_;
    }

    /* Test if the martix is a vector.
     * */
    bool is_vector() const {
        return _columns_ == 1 || _rows_ == 1;
    }
   

    /************************************
     *     Modify the actual matrix     *
     ************************************/

    /* Invert the bit in the position specified.
     * */
    void set (unsigned row, unsigned column) {
        row--;
        column--;
        if (row < _rows_ && column < _columns_) {
            uint64_t one = 1;
            _data_ [(row >> 3) * _lenc_ + (column >> 3)] ^= one << ((row & 7) << 3) + (column & 7);
        }
    }
    
    /* Multiply the column referenced by 'column' by 'multiplier'.
     * */
    void multr(unsigned row, bool multiplier) {
        row--;
        if (row < _rows_ && !multiplier) {
            uint64_t mask = Matrix::rvm[row & 7];
            row >>= 3;
            for (int i = _lenc_ * row; i < _lenc_ * (row + 1); i++) {
                _data_[i] &= ~mask;
            }
        }
    }
    
    /* Multiply the column referenced by 'column' by 'multiplier'.
     * */
    void multc(unsigned column, bool multiplier) { 
        column--;
        if(column < _columns_ && !multiplier) {
            uint64_t mask = Matrix::cvm[column & 7];
            column >>= 3;
            for (int i = column; i < _lenc_ * _lenr_; i += _lenc_) {
                _data_[i] &= ~mask;
            }
        }
    }

    /* Change the rows referenced by 'row1' and 'row2'.
     * */
    void changec (unsigned col1, unsigned col2) {
        col1--;
        col2--;
        if (col1 < _columns_ && col2 < _columns_ && col1 != col2) {
            uint64_t mask1 = col1 & 7;
            uint64_t mask2 = col2 & 7;
            if (mask2 > mask1) {
                std::swap (mask1, mask2);
                std::swap (col1, col2);
            }
            int k = mask1 - mask2;
            mask1 = Matrix::cvm[mask1];
            mask2 = Matrix::cvm[mask2];
            col1 = col1 >> 3;
            col2 = col2 >> 3;

            if (col2 == col1) {
                uint64_t t;
                mask1 = ~(mask1 | mask2);
                for (int i = col1; i < _lenr_ * _lenc_; i += _lenc_) {
                    t = _data_[i];
                    _data_[i] = (t & mask1) | ((t & mask2) << k) | ((t >> k) & mask2);
                }
            } else {
                uint64_t t1, t2;
                for (int i = 0; i < _lenr_ * _lenc_; i += _lenc_) {
                    t1 = _data_[i + col1];
                    t2 = _data_[i + col2];
                    _data_[i + col1] = t1 & ~mask1 | (t2 & mask2) << k;
                    _data_[i + col2] = t2 & ~mask2 | (t1 & mask1) >> k;
                }
            }
        }
    }

    /* Change the rows referenced by 'row1' and 'row2'.
     * */
    void changer(unsigned row1, unsigned row2) {
        row1--;
        row2--;
        if (row1 < _rows_ && row2 < _rows_ && row1 != row2) {
            uint64_t mask1 = row1 & 7;
            uint64_t mask2 = row2 & 7;
            if (mask2 > mask1) {
                std::swap (mask1, mask2);
                std::swap (row1, row2);
            }
            int k = (mask1 - mask2) << 3;
            mask1 = Matrix::rvm[mask1];
            mask2 = Matrix::rvm[mask2];
            row1 = row1 >> 3;
            row2 = row2 >> 3;
            
            if (row2 == row1) {
                uint64_t t;
                mask1 = ~(mask1 | mask2);
                for (int i = _lenc_ * row1; i < _lenc_ * (row1 + 1); i++) {
                    t = _data_[i];
                    _data_[i] = (t & mask1) | ((t & mask2) << k) | ((t >> k) & mask2);
                }
            } else {
                uint64_t t1, t2;
                for (int i = 0; i < _lenc_; i++) {
                    t1 = _data_[i + row1];
                    t2 = _data_[i + row2];
                    _data_[i + row1] = t1 & ~mask1 | (t2 & mask2) << k;
                    _data_[i + row2] = t2 & ~mask2 | (t1 & mask1) >> k;
                }
            }
        }
    }

    /* Operator to access an element.
     * */
    bool operator()(unsigned row, unsigned column) const {
        row--;
        column--;
        if (row < _rows_ && column < _columns_) {
            uint64_t one = 1;
            return _data_[(row >> 3)*_lenc_ + (column >> 3)] & (one << ((row & 7) << 3) + (column & 7));
        }
        return 0;
    }


    /**************************
     *     Get new matrix     *
     **************************/

    /* Return the transpose of the matrix. If this is a null matrix, the resulting also will be.
     * */
    Matrix traspose() {
        if (_columns_ != 0 && _rows_ != 0) {
            uint64_t * _data_new_ = new uint64_t[_lenr_ * _lenc_], res, mask1;
            for (int i = 0; i < _lenr_; i++) {
                for (int j = 0; j < _lenc_; j++) {
                    res = _data_[_lenc_*i + j];
                    for (int r = 49, k = 0; k < 7; k++, r -= 7) {
                        mask1 = Matrix::tvm[k];
                        res = res & ~(mask1 | Matrix::tvm[13 - k]) | (res & mask1) >> r | res << r & mask1;
                    }
                    _data_new_[_lenr_*j + i] = res;
                }
            }
            return Matrix(_columns_, _rows_, _data_new_);
        }
        return Matrix();
    }
    
    
    /* Return the attached matrix in the coordinates passed by parameter. If the coordinates exceed
     * the matrix range an null matrix will be returned.
     * */
    Matrix attached(unsigned row, unsigned col) {
        row--;
        col--;
        if(row < _rows_ && col < _columns_) {
            int i, j, k;
            uint64_t lenr, lenc, maskr = 0, maskc = 0, maskrf, maskcf, * _data_new_;
            lenr = (_rows_ + 6) >> 3;
            lenc = (_columns_ + 6) >> 3;
            _data_new_ = new uint64_t[lenr * lenc];

            for (i = (row & 7) + 1; i < 8; i++) {
                maskr |= Matrix::rvm[i];
            }
            for (i = (col & 7) + 1; i < 8; i++) {
                maskc |= Matrix::cvm[i];
            }

            maskrf = ~(maskr | Matrix::rvm[row & 7]);
            maskcf = ~(maskc | Matrix::cvm[col & 7]);
            col = col >> 3;
            row = row >> 3;

            /* copying the "static" part. */
            for (i = 0; i < lenr; i++) {
                for (j = i*_lenc_, k = i*lenc; k < (i + 1)*lenc; j++, k++) {
                    _data_new_[k] = _data_[j];
                }
            }

            /* shifting columns. */
            for (i = 0; i < lenr; i++) {
                j = i * _lenc_ + col;
                k = i * lenc + col;
                
                if (k < lenc * lenr) {

                    /* first iteration. */
                    _data_new_ [k] = maskcf & _data_new_[k] | (maskc & _data_new_[k]) >> 1;
                    j++;
                    k++;

                    /* middle iterations. */
                    for (; k < (i + 1) * lenc - 1; j++, k++) {
                        _data_new_ [k-1] |= _data_new_[k] << 7;
                        _data_new_ [k] = _data_new_[k] >> 1 ;
                    }

                    /* last iteration. */
                    if (j < (i + 1) * _lenc_) {
                        _data_new_ [k-1] |= _data_[j] << 7;
                        if (lenr == _lenr_) {
                            _data_new_ [k] = _data_[j] >> 1;
                        }
                    }
                }
            }

            /* shifting rows. */
            for (i = 0; i < lenc; i++) {
                j = _lenc_ * row + i;
                k = lenc * row + i;
                
                if (k < lenc * lenr) {

                    /* first iteration. */
                    _data_new_ [k] = maskrf & _data_new_[k] | (maskr & _data_new_[k]) >> 8;
                    j += _lenc_; 
                    k += lenc;

                    /* middle iterations. */
                    for (; k < lenc * (lenr - 1); j += _lenc_, k += lenc) {
                        _data_new_ [k-lenc] |= _data_new_ [k] << 56;
                        _data_new_ [k] = _data_new_ [k] >> 8;
                    }

                    /* last iteration. */
                    if (j < _lenc_ * _lenr_) {
                        _data_new_ [k-lenc] |= _data_[j] << 56;
                        if (lenc == _lenc_) {
                            _data_new_ [k] = _data_[j] >> 8;
                        }
                    }
                }
            }

            return Matrix(_rows_ - 1, _columns_ - 1, _data_new_);
        }
        return Matrix();
    }

    /* Matrix by Matrix operator.
     * */
    Matrix operator*(const Matrix & A) const {
        if (_columns_ == A._rows_) {
            uint64_t data_val, res, one = 1;
            uint64_t * _data_new_ = new uint64_t[_lenr_*A._lenc_];
            for (int i = 0; i < _lenr_ - 1; i++) {
                for (int j = 0, index = i * _lenc_; j < A._lenc_; j++, index++) {
                    multiply_by_index (i, j, 8, _lenc_, index, _data_, A._data_, _data_new_);
                }
            }
            /* Last iteration separated because (I think) is needed. */
            for (int j = 0, index = (_lenr_ - 1) * _lenc_; j < A._lenc_; j++, index++) {
                multiply_by_index (_lenr_ - 1, j, _rows_ & 7, _lenc_, index, _data_, A._data_, _data_new_);
            }
            return Matrix(_rows_, A._columns_, _data_new_);
        }
        return Matrix();
    }

    /* Matrix by constant operator.
     * */
    Matrix operator*(bool multiplier) const {
        if(_rows_ != 0 && _columns_ != 0){ 
            uint64_t * _data_new_;
            if (multiplier) {
                _data_new_ = new uint64_t[_lenc_ * _lenr_];
                memcpy (_data_new_, _data_, sizeof(uint64_t) * _lenc_ * _lenr_);
            } else {
                _data_new_ = new uint64_t[_lenc_ * _lenr_]{0};
            }
            return Matrix(_rows_, _columns_, _data_new_);
        }
        return Matrix();
    }

    /* Addition operator.
     * */
    Matrix operator+(const Matrix & M) const {
        if(_columns_ == M._columns_ && _rows_ == M._rows_) {
            uint64_t * _data_new_ = new uint64_t[_lenr_ * _lenc_];
            for (int i = 0; i < _lenr_ * _lenc_; i++) {
                _data_new_[i] = _data_[i] | M._data_[i];
            }
            return Matrix(_rows_, _columns_, _data_new_);
        } 
        return Matrix();
    } 
};

