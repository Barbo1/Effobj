
/* Here is an implementation of the matrices for fundamental types. In the future I will implement some
 * vectorization for the types doubles or floats (or both), and an integer type.
 * */

template<IntFloat T> requires arithmetric<T>
class Matrix<T> {
  private:
    T * _data_;
    unsigned _rows_;
    unsigned _columns_;

  public:

    /****************************
     *     Basic operations     *
     ****************************/

    /* Creation of a null Matrix. 
     * */
    Matrix () {
      this->_data_ = nullptr;
      this->_rows_ = 0;
      this->_columns_ = 0;
    }

    /* Zero Matrix constructor. 
     * */
    Matrix (unsigned rows, unsigned columns) {
      _rows_ = rows;
      _columns_ = columns;
      _data_ = new T[columns * rows];
      std::memset (_data_, 0, sizeof (T) * _rows_ * _columns_);
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

    /* Return a Matrix resulting of cast the elements from the actual type to the specified.
     * */
    template<arithmetric U>
      requires std::is_convertible_v<T, U>
      Matrix<U> cast() const {
        if (_rows_ != 0 && _columns_ != 0) {
          U * _data_new_ = new U[_rows_ * _columns_];
          for (unsigned i = 0; i < _rows_ * _columns_; i++) {
            _data_new_[i] = (U)_data_[i];
          }
          return Matrix<U>(_rows_, _columns_, _data_new_, true);
        } else {
          return Matrix<U>();
        }
      }



    /*************************************
     *     Return info of the Matrix     *
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

    /* Test if the Matrix is a null Matrix.
     * */
    bool is_null() const {
      return _rows_ == 0 || _columns_ == 0;
    }

    /* Test if the Matrix is a square Matrix.
     * */
    bool is_square() const {
      return _columns_ == _rows_;
    }

    /* Test if the martix is a vector.
     * */
    bool is_vector() const {
      return _columns_ == 1 || _rows_ == 1;
    }

    /* Test if the Matrix is stochastic(the sum of the elements in all rows is 1, and all elements
     * are between 0 and 1).
     * */
    bool is_stochastic() const { 
      unsigned i = 0, j;
      T accumulate;
      bool resul = false;

      while(resul && i < _columns_) {
        j = 0;
        accumulate = 0;
        while(resul && j < _rows_) {
          if (0 > _data_[_rows_*i + j] || _data_[_rows_*i + j] > 1) goto fin;
          accumulate += _data_[_rows_*i + j++];
        }
        if (accumulate != 1) goto fin;
        i++;
      }
      resul = true;
fin:
      return resul;
    }



    /************************************
     *     Modify the actual Matrix     *
     ************************************/

    /* Operator to access an element. Precondition: 1 <= row, column <= _rows_, _columns_
     * */
    T& operator()(unsigned row, unsigned column) const {
      row--;
      column--;
      return _data_[_rows_*row + column];
    }

    /* Change the rows referenced by 'col1' and 'col2'.
     * */
    void changec(unsigned col1, unsigned col2) {
      col1--;
      col2--;
      if(col1 <= _columns_ && col2 <= _columns_ && col1 != col2) {  
        for(unsigned i = 0; i < _rows_*_columns_; i += _columns_) {
          std::swap(_data_[i + col1], _data_[i + col2]);
        }
      }
    }

    /* Change the rows referenced by 'row1' and 'row2'.
     * */
    void changer(unsigned row1, unsigned row2) {
      row1--;
      row2--;
      if(row1 <= _columns_ && row2 <= _columns_ && row1 != row2) {
        unsigned aux1 = _rows_*row1;
        unsigned aux2 = _rows_*row2;
        for(unsigned i = 0; i < _rows_; i++) {
          std::swap(_data_[aux1 + i], _data_[aux2 + i]);
        }
      }
    }

    /* Multiply the row referenced by 'row' by 'multiplier'.
     * */
    void multr(unsigned row, float multiplier) {
      row--;
      if(row <= _rows_) { 
        for(unsigned i = _columns_ * row; i < _columns_ * (row + 1); i++) {
          _data_[i] *= multiplier;
        }
      }
    }

    /* Multiply the column referenced by 'column' by 'multiplier'.
     * */
    void multc(unsigned column, float multiplier) { 
      column--;
      if(column <= _columns_) {
        for(unsigned i = column; i < _columns_*_rows_; i += _columns_) {
          _data_[i] *= multiplier;
        }
      }
    }



    /**************************
     *     Get new Matrix     *
     **************************/

    /* Return the transpose of the Matrix. If this is a null Matrix, the resulting also will be.
     * */
    Matrix traspose() {
      if(_columns_ != 0 && _rows_ != 0) {
        unsigned i, j;
        T * _data_new_ = new T[_columns_*_rows_];
        for(i = 0; i < _rows_; i++) {
          for(j = 0; j < _columns_; j++) {
            _data_new_[_rows_*i + j] = _data_[_rows_*j + i];
          }
        }
        return Matrix(_columns_, _rows_, _data_new_, true);
      }
      return Matrix();
    }

    /* Return the attached Matrix in the coordinates passed by parameter. If the coordinates exceed
     * the Matrix range an null Matrix will be returned.
     * */
    Matrix attached(unsigned row_to_elim, unsigned col_to_elim) {
      row_to_elim--;
      col_to_elim--;
      if (row_to_elim <= _rows_ && col_to_elim <= _columns_) {
        int i, j, pos_i, pos_j;
        int _rows_new_ = _rows_-1, _columns_new_ = _columns_-1;
        T * _data_new_ = new T[_rows_new_*_columns_new_];
        for (i = 0; i < _rows_; i++) {
          pos_i = i - (i > row_to_elim);
          for (j = 0; j < _columns_; j++) {
            pos_j = j - (j > col_to_elim);
            if (i != row_to_elim && j != col_to_elim) {
              _data_new_[_rows_new_*pos_i + pos_j] = _data_[_rows_*i + j];
            }
          }
        }
        return Matrix(_rows_new_, _columns_new_, _data_new_, true);
      } else {
        return Matrix();
      }
    }

    /* Matrix by constant operator.
     * */
    Matrix operator*(T multiplier) const {
      if (_rows_ != 0 && _columns_ != 0){
        T * _data_new_ = new T[_columns_ * _rows_];
        for (unsigned i = 0; i < _rows_ * _columns_; i++) {
          _data_new_[i] = _data_[i] * multiplier;
        }
        return Matrix(_rows_, _columns_, _data_new_, true);
      }
      return Matrix();   
    }

    /* Matrix by Matrix operator.
     * */
    Matrix operator*(const Matrix & A) const {
      if (_columns_ == A._rows_) {
        unsigned i, j, k;
        unsigned res;
        T * _data_new_ = new T[_columns_*A._rows_];
        for (i = 0; i < _rows_; i++) {
          for (j = 0; j < A._columns_; j++) {
            res = _rows_*i + j;
            _data_new_[res] = _data_[_rows_*i] * A._data_[j];
            for (k = 1; k < _columns_; k++) {
              _data_new_[res] += _data_[_rows_*i + k] * A._data_[A._rows_*k + j];
            }
          }
        }
        return Matrix(_rows_, A._columns_, _data_new_, true);
      }
      return Matrix();
    }

    /* Addition operator.
     * */
    Matrix operator+(const Matrix & M) const {
      if(_columns_ == M._columns_ && _rows_ == M._rows_) {
        unsigned i = _columns_*_rows_;
        T * _data_new_ = new T[i];
        memcpy (_data_new_, _data_, sizeof(T) * i);
        for (int i = 0; i < _columns_ * _rows_; i++) {
          _data_new_[i] += _data_[i];
        }
        return Matrix(_rows_, _columns_, _data_new_, true);
      } else {
        return Matrix();
      } 
    }


    /* Return the invert of the Matrix. If the determinant of the Matrix is 0, 
     * a null Matrix is returned.
     * */
    Matrix<double> invert() {
      Matrix<double> ret = Matrix<double>();
      if(_rows_ != 0 && _columns_ != 0 && _columns_ == _rows_) {
        int current_dim = 0, i, j;
        double cm_1, cm_2;
        bool det_0 = true;

        /* Create a copy of the elements array converted to double. */
        double * _data_double_ = new double[_rows_ * _rows_];
        for(i = 0; i < _rows_; i++) {
          for(j = 0; j < _rows_; j++) {
            _data_double_[_rows_*i + j] = _data_[_rows_*i + j];
          }
        }

        /* Create an identity Matrix elements array. */
        double * _data_new_ = new double[_rows_ * _rows_];
        for(i = 0; i < _rows_; i++) {
          for(j = 0; j < _rows_; j++) {
            _data_new_[_rows_*i + j] = i == j;
          }
        }

        /* decending escalate. */
        while(current_dim < _rows_ && det_0) {
          i = current_dim;

          /* find a row that have an element != 0 in the current column. */
          while(i < _rows_ && _data_double_[_rows_*i + current_dim] == 0) {
            i++;
          }

          /* if finded... */
          if (i != _rows_) {
            /* if not the same column, then change both. */
            if (current_dim < i) {
              for (j = 0; j < _rows_; j++) {
                std::swap(_data_double_[_rows_*i + j], _data_double_[_rows_*current_dim + j]);
                std::swap(_data_new_[_rows_*i + j], _data_new_[_rows_*current_dim + j]);
              }
            }

            /* do the rows multiplication. */
            cm_1 = 1 / _data_double_[_rows_*current_dim + current_dim];
            for(i = current_dim+1; i < _rows_; i++) {
              cm_2 = _data_double_[_rows_*i + current_dim] * cm_1;
              if(cm_2 != 0) {
                for(j = current_dim; j < _columns_; j++) {
                  _data_double_[_rows_*i + j] -= cm_2 * _data_double_[_rows_*current_dim + j];
                }
                for(j = 0; j < _columns_; j++) {
                  _data_new_[_rows_*i + j] -= cm_2 * _data_new_[_rows_*current_dim + j];
                }
              }
            }
            current_dim++;
          } else {
            det_0 = false;
          }
        }

        /*
           rising escalate.
           */
        if (det_0) {
          current_dim--;
          while (current_dim >= 0) {
            cm_1 = 1 / _data_double_[_rows_*current_dim + current_dim];
            for (i = current_dim-1; i >= 0; i--) {
              cm_2 = _data_double_[_rows_*i + current_dim] * cm_1;
              if (cm_2 != 0) {
                for (j = 0; j < _rows_; j++) {
                  _data_new_[_rows_*i + j] -= cm_2 * _data_new_[_rows_*current_dim + j];
                }
              }
            }

            /* 
             * multiply the column by 1/cm_1 to make B(i,i) = 0 for all i 
             */
            for(j = 0; j < _rows_; j++) {
              _data_new_[_rows_ * current_dim + j] *= cm_1;
            }
            current_dim--;
          }
          ret = Matrix<double>(_rows_, _rows_, _data_new_);
        } else {
          delete [] _data_new_;
        }
        delete [] _data_double_;
      }
      return ret;
    }

    /* Return the determinant of the Matrix. 
     * */
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
};  

