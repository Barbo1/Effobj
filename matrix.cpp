#include "./matrix.hpp"
#include <utility>
#include <cmath>

Matrix::Matrix() {
   _data_ = nullptr;
   _rows_ = 0;
   _columns_ = 0;
}

Matrix::Matrix(unsigned rows, unsigned columns, float * & data) {
   _data_ = std::exchange(data, nullptr);
   _rows_ = rows;
   _columns_ = columns;
}

Matrix::Matrix(unsigned rows, unsigned columns, float * && data) {
   _data_ = data;
   _rows_ = rows;
   _columns_ = columns;
}

Matrix::Matrix(const Matrix & M) {
   _rows_ = M._rows_;
   _columns_ = M._columns_;
   if(_rows_ != 0 && _columns_ != 0) {
      unsigned length = _rows_ * _columns_;
      unsigned i;
      _data_ = new float[length];
      for(unsigned i = 0; i < length; i++) {
         _data_[i] = M._data_[i];
      }
   } else {
      _data_ = nullptr;
   }
}

Matrix::Matrix(Matrix && M) {
   _data_ = std::exchange(M._data_, nullptr);
   _rows_ = M._rows_;
   _columns_ = M._columns_;
}

Matrix::~Matrix(){
   if(_data_ != nullptr){
      delete [] _data_;
   }
}

Matrix Matrix::operator=(const Matrix & M) {
   _rows_ = M._rows_;
   _columns_ = M._columns_;
   if(_rows_ != 0 && _columns_ != 0){
      unsigned length = _rows_ * _columns_;
      unsigned i;
      _data_ = new float[length];
      for(unsigned i = 0; i < length; i++){
         _data_[i] = M._data_[i];
      }
   } else {
      _data_ = nullptr;
   }
   return *this;
}

Matrix Matrix::operator=(Matrix && M) {
   _data_ = std::exchange(M._data_, nullptr);
   _rows_ = M._rows_;
   _columns_ = M._columns_;
   return *this;
}

unsigned Matrix::rows() const { 
   return _rows_; 
}

unsigned Matrix::cols() const {
   return _columns_;
}

void Matrix::mult_row(unsigned row, float multiplier) {
   if(0 < row && row <= _rows_) {
      row--;
      for(unsigned i = 0; i < _columns_; i++) {
         _data_[_columns_*row + i] *= multiplier;
      }
   }
}

void Matrix::mult_column(unsigned column, float multiplier) { 
   if(0 < column && column <= _columns_) {
      column--;
      for(unsigned i = 0; i < _rows_; i++) {
         _data_[_columns_*i + column] *= multiplier;
      }
   }
}

void Matrix::change_columns(unsigned col1, unsigned col2) {
   if(0 != col1 && col1 <= _columns_ && 0 != col2 && col2 <= _columns_ && col1 != col2) {
      col1--;
      col2--;
      for(unsigned i = 0; i < _rows_; i++) {
         std::swap(_data_[_rows_*i + col1], _data_[_rows_*i + col2]);
      }
   }
}

void Matrix::change_rows(unsigned row1, unsigned row2) {
   if(0 != row1 && row1 <= _columns_ && 0 != row2 && row2 <= _columns_ && row1 != row2) {
      row1--;
      row2--;
      for(unsigned i = 0; i < _rows_; i++) {
         std::swap(_data_[_rows_*row1 + i], _data_[_rows_*row2 + i]);
      }
   }
}

bool Matrix::is_estocastic() const {
   if(_rows_ != _columns_){
      return false;
   }
   
   unsigned i = 0, j;
   float accumulate;
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

bool Matrix::is_square() const {
   return _columns_ == _rows_;
}

bool Matrix::is_vector() const {
   return _columns_ == 1 or _rows_ == 1;
}
  
float Matrix::operator()(unsigned row, unsigned column) const {
   if(row != 0 && row <= _rows_ && column != 0 && column <= _columns_){
      row--;
      column--;
      return _data_[_rows_*row + column];
   }
   return 0;
}

Matrix Matrix::operator*(float multiplier) const {
   float * _data_new_;
   _data_new_ = new float[_columns_*_rows_];
   for(unsigned i = 0; i < _rows_; i++) {
      for(unsigned j = 0; j < _columns_; j++){
         _data_new_[_rows_*i + j] = _data_[_rows_*i + j] * multiplier;
      }
   }
   return Matrix(_rows_, _columns_, _data_new_);;
}

Matrix Matrix::operator*(const Matrix & A) const {
   if(_columns_ == A._rows_) {
      unsigned i, j, k;
      unsigned res;
      float * _data_new_;
      _data_new_ = new float[_columns_*A._rows_];
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
      return Matrix(0, 0, nullptr);
   }
}

Matrix Matrix::operator+(const Matrix & M) const {
   if(_columns_ == M._columns_ && _rows_ == M._rows_) {
      unsigned i, j;
      float * _data_new_;
      _data_new_ = new float[_columns_*_rows_];
      for(i = 0; i < _rows_; i++) {
         for(j = 0; j < _columns_; j++) {
            _data_new_[_rows_*i + j] = _data_[_rows_*i + j] + M._data_[_rows_*i + j];
         }
      }
      return Matrix(_rows_, _columns_, _data_new_);
   } else {
      return Matrix(0, 0, nullptr);
   } 
}

void _printMatrix(Matrix A) {
    unsigned rows = A.rows(), cols = A.cols();
    if(rows != 0 && cols != 0){
        for(unsigned i = 1; i <= rows; i++){
            for(unsigned j = 1; j <= cols; j++){
                std::cout << A(i,j) << " ";
            }
            std::cout << std::endl;
        }
    }
}

Matrix Matrix::invert() {
   if(_rows_ != 0 && _columns_ != 0 && _columns_ == _rows_) {
      Matrix B = Matrix(*this);
      Matrix I = identity(_rows_);
      int current_dim = 0, i, j;
      float cm_1, cm_2;
      bool det_0 = true;

      /*
         decending escalate.
      */
      while(current_dim < _rows_ && det_0) {
         i = current_dim;

         /* find a row that have an element != 0 in the current column. */
         while(i < _rows_ && B._data_[_rows_*i + current_dim] == 0) {
            i++;
         }

         /* if finded... */
         if(i != _rows_) {
            /* if not the same column, then change both. */
            if(current_dim < i) {
               for(j = 0; j < _rows_; j++) {
                  std::swap(B._data_[_rows_*i + j], B._data_[_rows_*current_dim + j]);
                  std::swap(I._data_[_rows_*i + j], I._data_[_rows_*current_dim + j]);
               }
            }
            /* do the rows multiplication. */
            cm_1 = B._data_[_rows_*current_dim + current_dim];
            for(i = current_dim+1; i < _rows_; i++) {
               cm_2 = B._data_[_rows_*i + current_dim] / cm_1;
               if(cm_2 != 0) {
                  for(j = current_dim; j < _columns_; j++) {
                     B._data_[_rows_*i + j] -= cm_2*B._data_[_rows_*current_dim + j];
                  }
                  for(j = 0; j < _columns_; j++) {
                     I._data_[_rows_*i + j] -= cm_2*I._data_[_rows_*current_dim + j];
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
      if(det_0) {
         current_dim--;
         while(current_dim >= 0) {
            cm_1 = B._data_[_rows_*current_dim + current_dim];
            for(i = current_dim-1; i >= 0; i--) {
               cm_2 = B._data_[_rows_*i + current_dim] / cm_1;
               if(cm_2 != 0) {
                  for(j = 0; j < _rows_; j++) {
                     I._data_[_rows_*i + j] -= cm_2*I._data_[_rows_*current_dim + j];
                  }
               }
            }
            /* multiply the column by 1/cm_1 to make B(i,i) = 0 for all i */
            for(j = 0; j < _rows_; j++) {
               I._data_[_rows_*current_dim + j] /= cm_1;
            }
            current_dim--;
         }
         return I;
      }
   }
   return Matrix();
}

float Matrix::determinant() {
   float determinant = 1;
   if(_rows_ != 0 && _columns_ != 0 && _columns_ == _rows_) {
      Matrix B = Matrix(*this);
      unsigned current_dim = 0, i, j;
      float cm_1, cm_2;
      while(current_dim < _rows_ && determinant != 0) {
         i = current_dim;
         /* find a row that have an element != 0 in the current column. */
         while(i < _rows_ && B._data_[_rows_*i + current_dim] == 0) {
            i++;
         }
         /* if finded... */
         if(i != _rows_) {
            /* if not the same column, then change both. */
            if(current_dim < i) {
               for(j = 0; j < _rows_; j++) {
                  std::swap(B._data_[_rows_*i + j], B._data_[_rows_*current_dim + j]);
               }
               determinant *= -1;
            }
            /* do the rows multiplication. */
            cm_1 = B._data_[_rows_*current_dim + current_dim];
            for(i = current_dim+1; i < _rows_; i++) {
               cm_2 = B._data_[_rows_*i + current_dim] / cm_1;
               if(cm_2 != 0) {
                  for(j = current_dim; j < _columns_; j++) {
                     B._data_[_rows_*i + j] -= cm_2*B._data_[_rows_*current_dim + j];
                  }
               }
            }
            current_dim++;
            determinant *= cm_1;
         } else {
            determinant = 0;
         }
      }
   }
   return determinant;
}

Matrix Matrix::traspose() {
   if(_columns_ != 0 && _rows_ != 0) {
      unsigned i, j;
      float * _data_new_;
      _data_new_ = new float[_columns_*_rows_];
      for(i = 0; i < _rows_; i++) {
         for(j = 0; j < _columns_; j++) {
            _data_new_[_rows_*i + j] = _data_[_rows_*j + i];
         }
      }
      return Matrix(_columns_, _rows_, _data_new_);
   } else {
      return Matrix(0, 0, nullptr);
   }
}

Matrix Matrix::matrix_attached(unsigned row_to_elim, unsigned col_to_elim) {
   if(0 < row_to_elim && row_to_elim <= _rows_ && 0 < col_to_elim && col_to_elim <= _columns_) {
      row_to_elim--;
      col_to_elim--;
      unsigned i, j, pos_i, pos_j;
      unsigned _rows_new_ = _rows_-1, _columns_new_ = _columns_-1;
      float * _data_new_;
      _data_new_ = new float[_rows_new_*_columns_new_];
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
      return Matrix(0, 0, nullptr);
   }
}

Matrix identity(unsigned dimension) {
   if(dimension != 0){
      unsigned i, j;
      float * _data_new_;
      _data_new_ = new float[dimension * dimension];
      for(i = 0; i < dimension; i++) {
         for(j = 0; j < dimension; j++) {
            _data_new_[dimension*i + j] = i == j;
         }
      }
      return Matrix(dimension, dimension, _data_new_);
   } else {
      return Matrix(0, 0, nullptr);
   }
}

Matrix mfo(unsigned row, unsigned col, float elem) {
   if(row != 0 && col != 0) {
      unsigned i, j;
      float * _data_new_;
      _data_new_ = new float[row*col];
      for(i = 0; i < row; i++) {
         for(j = 0; j < col; j++) {
            _data_new_[row*i + j] = elem;
         }
      }
      return Matrix(row, col, _data_new_);
   } else {
      return Matrix(0, 0, nullptr);
   } 
}

