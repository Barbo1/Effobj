/* This library implements matrix objects with some methods to manipulate them, and some 
 * operations and functions. I would define the "null matrix" such as one that have a 
 * dimension(or both) equaly to 0. This one would be returned in case of error.
 * The class matrix is implemented in matrix.cpp, but Matrix_2sq, Matrix_4sq and
 * Matrix_8sq are not yet.
 * */

#pragma once

#include <type_traits>
#include <array>
#include <utility>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <immintrin.h>

#include "./needed.hpp"
#include "./needed.hpp"


/**********************
 *    Generic type    *
 **********************/

template<arithmetric T>
class Matrix {
  private:
    T * _data_;
    unsigned _rows_;
    unsigned _columns_;
  public:

    Matrix () noexcept;
    template<typename U> requires std::convertible_to <U, T*>
      Matrix (unsigned rows, unsigned columns, const U data, bool consume_data = false) noexcept;
    Matrix (const Matrix & M) noexcept;
    Matrix (Matrix && M) noexcept;
    Matrix& operator=(const Matrix & M) noexcept;
    Matrix& operator=(Matrix && M) noexcept;
    ~Matrix();

    /* Return the quantity of rows. */
    unsigned rows() const;

    /* Return the quantity of columns. */
    unsigned cols() const;

    /* Operator to access an element. 
     * Precondition: 1 <= row, column <= _rows_, _columns_ 
     * */
    T& operator() (unsigned row, unsigned column) const;

    /* Change the columns referenced by 'col1' and 'col2'. */
    void changec (unsigned col1, unsigned col2);

    /* Change the rows referenced by 'row1' and 'row2'. */
    void changer (unsigned row1, unsigned row2);

    /* Multiply the row referenced by 'row' by 'multiplier'. */
    void multr (unsigned row, float multiplier);

    /* Multiply the column referenced by 'column' by 'multiplier'. */
    void multc (unsigned column, float multiplier);

    /* Return a matrix resulting of cast the elements from the 
     * actual type to the specified.
     * */
    template<arithmetric U> requires std::is_convertible_v<T, U>
      Matrix<U> cast() const;

    /* Test if the matrix is a null matrix. */
    bool is_null() const;

    /* Test if the matrix is a square matrix. */
    bool is_square() const;

    /* Test if the martix is a vector. */
    bool is_vector() const;

    /* Return the transpose of the matrix. If this is a null matrix, 
     * the resulting also will be.
     * */
    Matrix traspose();

    /* Return the attached matrix in the coordinates passed by parameter. 
     * If the coordinates exceed the matrix range an null matrix will be returned.
     * */
    Matrix attached(unsigned row_to_elim, unsigned col_to_elim);

    /* Matrix by constant operator. */
    Matrix operator*(T multiplier) const;

    /* Matrix by Matrix operator. */
    Matrix operator*(const Matrix & A) const;

    Matrix operator+ (const Matrix & M) const;

    /* Return the inverse of the Matrix. If this is a null Matrix, or the determinant 
     * is 0, a null Matrix will be returned.
     * */
    Matrix invert();

    /* Return the determinant of the Matrix. If this is a null Matrix, 0 will be returned.
     * */
    T determinant();
};  


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
    static constexpr std::array<uint64_t, 14> tvm {
      72057594037927936ULL, 144396663052566528ULL, 288794425616760832ULL, 577588855528488960ULL, 
        1155177711073755136ULL, 2310355422147575808ULL, 4620710844295151872ULL, 36099303471055874ULL, 
        141012904183812ULL, 550831656968ULL, 2151686160ULL, 8405024ULL, 32832ULL, 128ULL
    };

    static constexpr std::array<uint64_t, 8> cvm {
      72340172838076673ULL, 144680345676153346ULL, 289360691352306692ULL, 578721382704613384ULL, 
        1157442765409226768ULL, 2314885530818453536ULL, 4629771061636907072ULL, 9259542123273814144ULL
    };

    static constexpr std::array<uint64_t, 8> rvm {
      255ULL, 65280ULL, 16711680ULL, 4278190080ULL, 1095216660480ULL, 280375465082880ULL, 
        71776119061217280ULL, 18374686479671623680ULL
    };

    static constexpr std::array<uint64_t, 8> cvm_sum {[](const std::array<uint64_t, 8> & cvm) {
      std::array<uint64_t, 8> arr;
      arr[7] = cvm[7];
      for (int i = 6; i >= 0; i--) { 
        arr[i] = cvm[i] | arr[i+1]; 
      }
      return arr;
    }(cvm)};

    static constexpr std::array<uint64_t, 8> rvm_sum = {[](const std::array<uint64_t, 8> & rvm) {
      std::array<uint64_t, 8> arr;
      arr[7] = rvm[7];
      for (int i = 6; i >= 0; i--) { 
        arr[i] = rvm[i] | arr[i+1]; 
      }
      return arr;
    }(rvm)};

    /* Constructor to not allocate so much memory. */
    Matrix (unsigned rows, unsigned columns, uint64_t * data);

    /* Method needed to make the multiplication. */
    static void multiply_by_index (
      int i, 
      int j, 
      int rows, 
      int _lenc_, 
      int index,
      uint64_t * _data_, 
      uint64_t * _A_data_, 
      uint64_t * _data_new_ 
    );

  public:

    /****************************
     *     Basic operations     *
     ****************************/

    Matrix() noexcept;
    Matrix (unsigned rows, unsigned columns, bool* data, bool consume_data = false) noexcept;
    Matrix (unsigned rows, unsigned columns) noexcept;
    Matrix(const Matrix & M) noexcept;
    Matrix(Matrix && M) noexcept;
    Matrix operator=(const Matrix & M) noexcept;
    Matrix operator=(Matrix && M) noexcept;
    ~Matrix();

    /* Return a matrix resulting of cast the elements from the actual type to the specified.
     * */
    template<arithmetric U>
    requires std::is_convertible_v <bool, U>
    Matrix<U> cast();


    /*************************************
     *     Return info of the matrix     *
     *************************************/

    /* Return the quantity of rows.  
     * */
    unsigned rows() const;

    /* Return the quantity of columns.  
     * */
    unsigned cols() const;

    /* Test if the matrix is a null matrix.
     * */
    bool is_null() const;

    /* Test if the matrix is a square matrix.
     * */
    bool is_square() const;

    /* Test if the martix is a vector.
     * */
    bool is_vector() const;


    /************************************
     *     Modify the actual matrix     *
     ************************************/

    /* Invert the bit in the position specified.
     * */
    void set (unsigned row, unsigned column);

    /* Multiply the column referenced by 'column' by 'multiplier'.
     * */
    void multr(unsigned row, bool multiplier);

    /* Multiply the column referenced by 'column' by 'multiplier'.
     * */
    void multc(unsigned column, bool multiplier);

    /* Change the rows referenced by 'row1' and 'row2'.
     * */
    void changec (unsigned col1, unsigned col2);

    /* Change the rows referenced by 'row1' and 'row2'.
     * */
    void changer(unsigned row1, unsigned row2);

    /* Operator to access an element.
     * */
    bool operator()(unsigned row, unsigned column) const;

    /**************************
     *     Get new matrix     *
     **************************/

    /* Return the transpose of the matrix. If this is a null matrix, the resulting also will be.
     * */
    Matrix traspose();

    /* Return the attached matrix in the coordinates passed by parameter. If the coordinates exceed
     * the matrix range an null matrix will be returned.
     * */
    Matrix attached (unsigned row, unsigned col);

    /* Matrix by Matrix operator.
     * */
    Matrix operator*(const Matrix & A) const;
    /* Matrix by constant operator.
     * */
    Matrix operator*(bool multiplier) const;
    /* Addition operator.
     * */
    Matrix operator+(const Matrix & M) const;
};



/**********************************
 *    Generic Size, Float type    *
 **********************************/

/* float vector of size 4 */


template<>
class Matrix<float> {
  private:
    fv_x4 * _data_;
    unsigned _rows_;
    unsigned _columns_;
    unsigned _length_;

  public:
    Matrix () noexcept;
    Matrix (unsigned rows, unsigned columns, fv_x4 * data, bool consume = true) noexcept;
    Matrix (unsigned rows, unsigned columns, float * data, bool consume = true) noexcept;
    Matrix (const Matrix & M) noexcept;
    Matrix (Matrix && M) noexcept;
    Matrix operator= (const Matrix & M) noexcept;
    Matrix operator=(Matrix && M) noexcept;

    /* Return a matrix resulting of cast the elements from the actual type 
     * to the specified.
     * */
    template<arithmetric U>
    requires (!std::is_same_v<U, float>)
    Matrix<U> cast();

    /* Return the quantity of rows.  
     * */
    unsigned rows() const;

    /* Return the quantity of columns.  
     * */
    unsigned cols() const;

    /* Change the rows referenced by 'row1' and 'row2'.
     * */
    void changec(unsigned col1, unsigned col2);

    /* Change the rows referenced by 'row1' and 'row2'.
     * */
    void changer(unsigned row1, unsigned row2);

    /* Multiply the row referenced by 'row' by 'multiplier'.
     * */
    void multr(unsigned row, float multiplier);
    
    /* Multiply the column referenced by 'column' by 'multiplier'.
     * */
    void multc(unsigned column, float multiplier);
    
    /* Test if the matrix is a null matrix.
     * */
    bool is_null () const;

    /* Test if the matrix is a square matrix.
     * */
    bool is_square () const;

    /* Test if the martix is a vector. A Matrix is a vector if only one of 
     * his dimentions is 1.
     * */
    bool is_vector () const;

    /* Test if the matrix is stochastic(the sum of the elements in all rows 
     * is 1, and all elements are between 0 and 1).
     * */
    bool is_stochastic () const;
      
    /* Operator to access an element.
     * */
    float operator () (unsigned row, unsigned column) const;
 
    /* Return the transpose of the matrix. If this is a null matrix, the 
     * resulting also will be.
     * */
    Matrix traspose ();
    
    /* Return the attached matrix in the coordinates passed by parameter. 
     * If the coordinates exceed the matrix range an null matrix will be 
     * returned.
     * */
    Matrix attached (unsigned row_to_elim, unsigned col_to_elim);

    /* Matrix by constant operator.
     * */
    Matrix operator*(float multiplier) const;

    /* Matrix by Matrix operator.
     * */
    Matrix operator*(const Matrix & A) const;

    /* Addition operator.
     * */
    Matrix operator+(const Matrix & M) const;
   
    /* Return the inverse of the matrix. If this is a null matrix, or the 
     * determinant is 0, a null matrix will be returned.
     * */
    Matrix invert();
    
    /* Return the determinant of the matrix. If this is a null matrix, or 
     * the dimentions don't match, the returned value is 0.
     * */
    float determinant();
};  



/******************************
 *    Functions definition    *
 ******************************/

/* Return an identity matrix with the dimention passed by parameter.
 * */
template<arithmetric T>
Matrix<T> identity(unsigned dimension);

/* Return an identity matrix with all the positions equal to elem.
 * */
template<arithmetric T>
Matrix<T> mfo(unsigned row, unsigned col, T elem);
