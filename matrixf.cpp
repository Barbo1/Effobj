#include <immintrin.h>

/**********************************
 *    Generic Size, float type    *
 **********************************/

// float vector of size 4
union fv_x4{
    __m128 _v;
    float _f[4];
};

template<>
class Matrix<float>{
private:
    fv_x4 * _data_;
    unsigned _rows_;
    unsigned _columns_;
    unsigned _length_;
public:
    Matrix() {
       _data_ = nullptr;
       _length_ = 0;
       _rows_ = 0;
       _columns_ = 0;
    }

    Matrix(unsigned rows, unsigned columns, fv_x4 * data){
        _rows_ = rows;
        _columns_ = columns;
        _length_ = (columns + 3)/4;
        _data_ = data;
    }

    template<typename U>
    requires std::is_same_v< std::remove_reference_t<U>, float* >
    Matrix(unsigned rows, unsigned columns, U && data){
        _rows_ = rows;
        _columns_ = columns;
        if(_rows_ != 0 && _columns_ != 0){
            unsigned i, j;
            _length_ = (_columns_ + 3) / 4;
            _data_ = new fv_x4[_length_ * _rows_];
            
            // initialize with 0's the last fv_x4
            for(i = 1; i <= _rows_; i++){
                _data_[i*_length_ - 1]._v = _mm_setzero_ps();
            }

            for(i = 0; i < _rows_; i++) {
                for(j = 0; j < _columns_; j++){
                    _data_[i*_length_ + j/4]._f[j % 4] = data[i*_columns_ + j];
                }
            }
            delete [] data;
        }
        data = nullptr;
    }
    
    Matrix(const Matrix & M) {
        _rows_ = M._rows_;
        _columns_ = M._columns_;
        _length_ = M._length_;
        unsigned length = _rows_*_length_;
        _data_ = new fv_x4[length];
        memcpy(_data_, M._data_, sizeof(fv_x4)*length);
    }
   
    Matrix(Matrix && M) noexcept {
        _data_ = std::exchange(M._data_, nullptr);
        _rows_ = std::exchange(M._rows_, 0);
        _length_ = std::exchange(M._length_, 0);
        _columns_ = std::exchange(M._columns_, 0);
    }

    Matrix operator=(const Matrix & M) {
        _rows_ = M._rows_;
        _columns_ = M._columns_;
        _length_ = M._length_;
        if (_data_ != nullptr) {
            delete [] _data_;
            _data_ = nullptr;
        }
        if(_rows_ != 0 && _columns_ != 0) {
            unsigned length = _rows_*_length_;
            _data_ = new fv_x4[length];
            memcpy(_data_, M._data_, sizeof(fv_x4)*length);
        }
        return *this;
    }

    Matrix operator=(Matrix && M) noexcept {
        delete [] _data_;
        _data_ = std::exchange(M._data_, nullptr);
        _rows_ = M._rows_;
        _columns_ = M._columns_;
        _length_ = M._length_;
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
    requires (!std::is_same_v<U, float>)
    Matrix<U> cast() {
        if(_rows_ != 0 && _columns_ != 0) {
            unsigned length = _rows_ * _length_;
            U * _data_new_ = new U[length];
            for(signed char i = 0; i < _rows_; i++) {
                for(signed char j = 0; j < _columns_; j++){
                    _data_new_[i*_columns_ + j] = (U)_data_[(i*length + j) / 4]._f[j % 4];
                }
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
                std::swap(_data_[i*_length_ + col1 / 4]._f[col1 % 4], 
                        _data_[i*_length_ + col2 / 4]._f[col2 % 4]);
            }
        }
    }

    /*
     *  Change the rows referenced by 'row1' and 'row2'.
     * */
    void changer(unsigned row1, unsigned row2) {
        row1--;
        row2--;
        if(row1 <= _rows_ && row2 <= _rows_ && row1 != row2) {
            for(unsigned i = 0; i < _length_; i++) {
                std::swap(_data_[_length_*row1 + i]._v, _data_[_length_*row2 + i]._v);
            }
        }
    }
    
    /*
     *  Test if the matrix is a null matrix.
     **/
    bool is_null() {
        return _rows_ == 0 || _columns_ == 0;
    }

    /*
     *  Test if the matrix is a square matrix.
     **/
    bool is_square() const {
        return _columns_ == _rows_;
    }

    /*
     *  Test if the martix is a vector. A Matrix is a vector if only one of his dimentions is 1.
     **/
    bool is_vector() const {
        return _columns_ != 0 && _rows_ != 0 && (_columns_ == 1 ^ _rows_ == 1);
    }
      
    /*
     *  Operator to access an element.
     * */
    float operator()(unsigned row, unsigned column) const {
        row--;
        column--;
        if(row <= _rows_ && column <= _columns_){
            return _data_[row*_length_ + column/4]._f[column % 4];
        }
        return 0;
    }
 
    /*
     *  Return the transpose of the matrix. If this is a null matrix, the resulting also will be.
     **/
    Matrix traspose() {
        if(_columns_ != 0 && _rows_ != 0) {
            unsigned i, j;
            __m128 zero = _mm_setzero_ps();
            unsigned length = (_rows_ + 3)/4;
            fv_x4 * _data_new_ = new fv_x4[_columns_ * length];
            for(i = 0; i < _columns_; i++) {
                _data_new_[length*(i+1) - 1]._v = zero;
                for(j = 0; j < _rows_; j++) {
                    _data_new_[length*i + j/4]._f[j % 4] = _data_[_length_*j + i/4]._f[i % 4];
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
            unsigned res_1, res_2, res_3, i, j;
            unsigned _rows_new_ = _rows_-1, _columns_new_ = _columns_-1;
            unsigned length_new = (_columns_new_ + 3) / 4;
            fv_x4 * _data_new_ = new fv_x4[_rows_new_ * length_new];
            for(i = 0; i < _rows_; i++) {
                res_1 = length_new * (i - (i > row_to_elim));
                res_2 = _length_*i;
                for(unsigned j = 0; j < _columns_; j++) {
                    if(i != row_to_elim && j != col_to_elim) {
                        res_3 = (j - (j > col_to_elim));
                        _data_new_[res_1 + res_3 / 4]._f[res_3 % 4] = 
                            _data_[res_2 + j / 4]._f[j % 4];
                    }
                }
            }
            return Matrix(_rows_new_, _columns_new_, _data_new_);
        } else {
            return Matrix();
        }
    }

    /*
     *  Test if the matrix is stochastic(the sum of the elements in all rows is 1, and all elements
     *  are between 0 and 1).
     * */
    bool is_stochastic() const { 
        unsigned i, j, pos;
        __m128 res;
        __m128 zeros = _mm_setzero_ps(), ones = _mm_set1_ps(1);
        fv_x4 accumulate;
        bool resul = true;

        i = 0;
        while(resul && i < _rows_) {
            j = 0;
            accumulate._v = _data_[_length_*i]._v;
            for(j = 1; j < _length_; j++) {
                res = _data_[_length_*i + j]._v;
                resul = !_mm_testc_ps(
                            _mm_or_ps(_mm_cmp_ps(res, ones, 1), _mm_cmp_ps(res, zeros, 14)),
                            _mm_set1_ps(0xffffffff)
                        );
                accumulate._v = _mm_add_ps(res, accumulate._v);
            }
            resul = (accumulate._f[0] + accumulate._f[1] + accumulate._f[2] + accumulate._f[3]) == 1;
            i++;
        }
        return resul;
    }

    /*
     *  Multiply the row referenced by 'row' by 'multiplier'.
     * */
    void multr(unsigned row, float multiplier) {
        row--;
        if(row <= _rows_) { 
            unsigned i;
            __m128 res = _mm_set1_ps(multiplier);
            for(i = _length_ * row; i < _length_ * (row + 1); i++) {
                _data_[i]._v = _mm_mul_ps(_data_[i]._v, res);
            }
        }
    }
    
    /*
     *  Multiply the column referenced by 'column' by 'multiplier'.
     * */
    void multc(unsigned column, float multiplier) { 
        column--;
        if(column <= _columns_) {
            unsigned pos, i;
            for(i = 0; i < _rows_; i++) {
                pos = _length_*i + column / 4;
                _data_[pos / 4]._f[column % 4] *= multiplier;
            }
        }
    }

    /* 
     *  Matrix by constant operator.
     **/
    Matrix operator*(float multiplier) const {
        if(_rows_ != 0 && _columns_ != 0){
            unsigned j;
            unsigned length = _rows_ * _length_;
            fv_x4 * _data_new_ = new fv_x4[length];
            __m128 res = _mm_set1_ps(multiplier);
            for(j = 0; j < length; j++) {
                _data_new_[j]._v = _mm_mul_ps(_data_[j]._v, res);
            }
            return Matrix(_rows_, _columns_, _data_new_);
        }
        return Matrix();   
    }

    /* 
     *  Matrix by Matrix operator.
     **/
    Matrix operator*(const Matrix & A) const {
       if(_columns_ == A._rows_) {
            unsigned i, j, k;
            __m128 res_1, zero = _mm_setzero_ps();
            fv_x4 * _res_, * _data_new_;
            
            _res_ = new fv_x4[A._columns_ * _length_];
            for(i = 0; i < A._columns_; i++){
                _res_[_length_*(i+1) - 1]._v = zero;
                for(j = 0; j < A._rows_; j++) {
                    _res_[_length_*i + j/4]._f[j % 4] = A._data_[A._length_*j + i/4]._f[i % 4];
                }
            }
            
            _data_new_ = new fv_x4[_rows_ * A._length_];
            for(i = 0; i < _rows_; i++){
                for(j = 0; j < A._columns_; j++) {
                    res_1 = zero;
                    for(k = 0; k < _length_; k++) {
                        res_1 = _mm_add_ps(
                                    res_1,
                                    _mm_mul_ps(_data_[_length_*i + k]._v, _res_[_length_*j + k]._v)
                                );
                    }
                    _data_new_[i*A._length_ + j/4]._f[j % 4] = res_1[0] + res_1[1] + res_1[2] + res_1[3];
                }
            }
            delete [] _res_;
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
            fv_x4 * _data_new_ = new fv_x4[_rows_*_length_];
            for(i = 0; i < _rows_*_length_; i++) {
                _data_new_[i]._v = _mm_add_ps(M._data_[i]._v, _data_[i]._v);
            }
            return Matrix(_rows_, _columns_, _data_new_);
        } else {
            return Matrix();
        } 
    }
   
    /*
     *  Return the inverse of the matrix. If this is a null matrix, or the determinant is 0, a
     *  null matrix will be returned.
     * */
    Matrix invert() {
        Matrix ret = Matrix();
        if(_rows_ != 0 && _columns_ != 0 && _columns_ == _rows_) {
            int current_dim = 0, i, j;
            float cm_1, cm_2;
            unsigned * res_1 = new unsigned[3];
            bool det_0 = true;
            fv_x4 * _data_new_, * _iden_;
            __m128 res = _mm_setzero_ps();

            _data_new_= new fv_x4[_rows_ * _length_];
            _iden_ = new fv_x4[_rows_ * _length_];
            for(i = 0; i < _rows_ * _length_; i++) {
                _data_new_[i] = _data_[i];
                _iden_[i]._v = res;
            }
            for(i = 0; i < _rows_; i++){
                _iden_[_length_*i + i/4]._f[i % 4] = 1;
            }

            while(current_dim < _rows_ && det_0) {
                i = current_dim;
                res_1[0] = current_dim / 4;
                res_1[1] = current_dim % 4;
                res_1[2] = _length_*current_dim;
                while(i < _rows_ && _data_new_[_length_*i + res_1[0]]._f[res_1[1]] == 0) {
                    i++;
                }

                if(i != _rows_) {
                    if(current_dim < i) {
                        for(j = 0; j < _length_; j++) {
                            std::swap(_data_new_[_length_*i + j]._v, _data_new_[res_1[2] + j]._v);
                            std::swap(_iden_[_length_*i + j]._v, _iden_[res_1[2] + j]._v);
                        }
                    }
                    cm_1 = _data_new_[res_1[2] + res_1[0]]._f[res_1[1]];
                    for(i = current_dim+1*_length_; i < _rows_*_length_; i += _length_) {
                        cm_2 = _data_new_[i + res_1[0]]._f[res_1[1]] / cm_1;
                        if(cm_2 != 0) {
                            res = _mm_set1_ps(cm_2);
                            for(j = res_1[0]; j < _length_; j++) {
                                _data_new_[i + j]._v = _mm_fnmadd_ps(
                                        res, 
                                        _data_new_[res_1[2] + j]._v, 
                                        _data_new_[i + j]._v);
                            }
                            for(j = 0; j < _length_; j++) {
                                _iden_[i + j]._v = _mm_fnmadd_ps(
                                        res,
                                        _iden_[res_1[2] + j]._v,
                                        _iden_[i + j]._v);
                            }
                        }
                    }
                    current_dim++;
                } else {
                    det_0 = false;
                }
            }
 
            if(det_0) {
                current_dim--;
                while(current_dim >= 0) {
                    res_1[0] = current_dim / 4;
                    res_1[1] = current_dim % 4;
                    res_1[2] = _length_*current_dim;
                    cm_1 = _data_new_[res_1[2] + res_1[0]]._f[res_1[1]];
                    for(i = (current_dim-1) * _length_; i >= 0; i -= _length_) {
                        cm_2 = _data_new_[i + res_1[0]]._f[res_1[1]] / cm_1;
                        res = _mm_set1_ps(cm_2);
                        if(cm_2 != 0) {
                            for(j = 0; j < _length_; j++) {
                                _iden_[i + j]._v = _mm_fnmadd_ps(
                                        res, 
                                        _iden_[res_1[2] + j]._v,
                                        _iden_[i + j]._v);
                            }
                        }
                    }
                    cm_1 = 1/cm_1;
                    res = _mm_set1_ps(cm_1);
                    for(j = res_1[2]; j < res_1[2] + _length_; j++) {
                        _iden_[j]._v = _mm_mul_ps(_iden_[j]._v, res);
                    }
                    current_dim--;
                }
                ret = Matrix(_rows_, _rows_, _iden_);
            } else {
                delete [] _iden_;
            }
            delete [] res_1;
            delete [] _data_new_;
        }
        return ret;
    }
    
    /*
     *  Return the determinant of the matrix. If this is a null matrix, or the dimentions don't match, the
     *  returned value is 0.
     * */
    float determinant() {
        float determinant;
        if(_rows_ != 0 && _columns_ != 0 && _columns_ == _rows_) {
            unsigned current_dim = 0, i, j;
            float cm_1, cm_2;
            unsigned * res_1 = new unsigned[3];
            fv_x4 * _data_new_;
            __m128 res;
            
            determinant = 1;
            _data_new_= new fv_x4[_rows_ * _length_];
            for(i = 0; i < _rows_ * _length_; i++) {
                _data_new_[i]._v = _data_[i]._v;
            }
             
            while(determinant != 0 && current_dim < _rows_) {
                i = current_dim;
                res_1[0] = current_dim / 4;
                res_1[1] = current_dim % 4;
                res_1[2] = current_dim * _length_;
                while(i < _rows_ && _data_new_[_length_*i + res_1[0]]._f[res_1[1]] == 0) {
                    i++;
                }
                
                if(i != _rows_) {
                    if(current_dim < i) {
                        for(j = 0; j < _rows_; j++) {
                            std::swap(_data_new_[_length_*i + j/4]._v, _data_new_[res_1[2] + j/4]._v);
                        }
                        determinant *= -1;
                    }
                    cm_1 = _data_new_[res_1[2] + res_1[0]]._f[res_1[1]];
                    for(i = current_dim+1; i < _rows_; i++) {
                        cm_2 = _data_new_[_length_*i + res_1[0]]._f[res_1[1]] / cm_1;
                        res = _mm_set1_ps(cm_2);
                        if(cm_2 != 0) {
                            for(j = current_dim/4; j < _length_; j++) {
                                _data_new_[_length_*i + j]._v = 
                                    _mm_fnmadd_ps(res, 
                                        _data_new_[res_1[2] + j]._v,
                                        _data_new_[_length_*i + j]._v
                                    );
                            }
                        }
                    }
                    current_dim++;
                    determinant *= cm_1;
                } else {
                    determinant = 0;
                }
            }
            delete [] res_1;
            delete [] _data_new_;
        } else {
            determinant = 0;
        }
        return determinant;
    } 
};  

