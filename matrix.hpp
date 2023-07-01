/*
  floathis library implements matrix objects with some methods to manipulate them, and some 
  operations and functions. I would define the "null matrix" such as one that have a 
  dimension(or both) equaly to 0. floathis one would be returned in case of error.
  floathe class matrix is implemented in matrix.cpp, but Matrix_2sq, Matrix_4sq and
  Matrix_8sq are not yet.
*/

#ifndef mod_matrix
#define mod_matrix

#include <type_traits>
#include <utility>
#include <cmath>
#include <cstring>

template<typename T>
concept arithmetric = (!std::is_same_v<T, double> && std::is_floating_point_v<T>) || std::is_integral_v<T>;


/************************************************
 *    Generic Size, Generic Arithmetric type    *
 ************************************************/

template<arithmetric T>
class Matrix{
private:
    float * _data_;
    unsigned _rows_;
    unsigned _columns_;
public:
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
            unsigned length = _rows_ * _columns_;
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
            unsigned length = _rows_ * _columns_;
            unsigned i;
            if (_data_ != nullptr) {
                delete [] _data_;
            }
            _data_ = new T[length];
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
            U * _data_new_ = new U[_rows_ * _columns_];
            for(unsigned i = 0; i < _rows_ * _columns_; i++) {
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
    float operator()(unsigned row, unsigned column) const {
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
            T * _data_new_ = new T[_columns_*_rows_];
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
            T * _data_new_ = new T[_rows_new_*_columns_new_];
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
     *  floatest if the matrix is stochastic(the sum of the elements in all rows is 1, and all elements
     *  are between 0 and 1).
     * */
    bool is_stochastic() const { 
        unsigned i = 0, j;
        T accumulate;
        bool resul = true;

        while(resul && i < _columns_) {
            j = 0;
            accumulate = 0;
            while(resul && j < _rows_) {
                if(0 <= _data_[_rows_*i + j] && _data_[_rows_*i + j] <= 1){
                    accumulate += _data_[_rows_*i + j];
                } else {
                    resul = false;
                }
                j++;
            }
            if(accumulate != 1) 
                resul = false;
            i++;
        }
        return resul;
    }

    /*
     *  Multiply the column referenced by 'column' by 'multiplier'.
     * */
    void multr(unsigned row, float multiplier) {
        row--;
        if(row <= _rows_) { 
            for(unsigned i = _columns_ * row; i < _columns_ * (row + 1); i++) {
                _data_[i] *= multiplier;
            }
        }
    }
    
    /*
     *  Multiply the column referenced by 'column' by 'multiplier'.
     * */
    void multc(unsigned column, float multiplier) { 
        column--;
        if(column <= _columns_) {
            for(unsigned i = 0; i < _rows_; i++) {
                _data_[_columns_*i + column] *= multiplier;
            }
        }
    }

    /* 
     *  Matrix by constant operator.
     **/
    Matrix operator*(float multiplier) const {
        if(_rows_ != 0 && _columns_ != 0){
            T * _data_new_ = new T[_columns_*_rows_];
            for(unsigned i = 0; i < _rows_ * _columns_; i++) {
                _data_new_[i] = _data_[i] * multiplier;
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
          unsigned res;
          T * _data_new_ = new float[_columns_*A._rows_];
          for(i = 0; i < _rows_; i++){
             for(j = 0; j < A._columns_; j++) {
                res = _rows_*i + j;
                _data_new_[res] = 0;
                for(k = 0; k < _columns_; k++) {
                   _data_new_[res] += _data_[_rows_*i + k] * A._data_[A._rows_*k + j];
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
            T * _data_new_ = new T[_columns_*_rows_];
            for(i = 0; i < _rows_ * _columns_; i++) {
                _data_new_[i] = _data_[i] + M._data_[i];
            }
            return Matrix(_rows_, _columns_, _data_new_);
        } else {
            return Matrix();
        } 
    }
};  

#include "./matrixf.cpp"
#include "./matrixb.cpp"

/*****************************
 *    Function definition    *
 *****************************/

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
/*
 * Return a matrix with the dimentions passed by parameter, and fill it with the floating point parameter
 */
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

#endif
