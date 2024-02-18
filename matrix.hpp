/*
  This library implements matrix objects with some methods to manipulate them, and some 
  operations and functions. I would define the "null matrix" such as one that have a 
  dimension(or both) equaly to 0. This one would be returned in case of error.
  The class matrix is implemented in matrix.cpp, but Matrix_2sq, Matrix_4sq and
  Matrix_8sq are not yet.
*/

#ifndef __Matrix_mod
#define __Matrix_mod

#include <type_traits>
#include <utility>
#include <cmath>
#include <cstring>
#include <cstdint>
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
        
        #include "./matrix_files/basic_operations.cpp"
        
        #include "./matrix_files/get_info.cpp"
        
        #include "./matrix_files/col_row_manipulation.cpp"
        
        #include "./matrix_files/cast.cpp"
        
        #include "./matrix_files/is_methods.cpp"
        
        #include "./matrix_files/traspose.cpp"
      
        #include "./matrix_files/attached.cpp"
        
        #include "./matrix_files/mult_methods.cpp"

        #include "./matrix_files/add_method.cpp"

        #include "./matrix_files/invert.cpp"
        
        #include "./matrix_files/determinant.cpp"
};  

#include "./matrix_files/Xmatrixif.cpp"

#include "./matrix_files/Xmatrixb.cpp"

/******************************
 *    Functions definition    *
 ******************************/

#include "./matrix_files/funcdef.cpp"

#endif
