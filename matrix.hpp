/*
  This library implements matrix objects with some methods to manipulate them, and some 
  operations and functions. I would define the "null matrix" such as one that have a 
  dimension(or both) equaly to 0. This one would be returned in case of error.
  The class matrix is implemented in matrix.cpp, but Matrix_2sq, Matrix_4sq and
  Matrix_8sq are not yet.
*/

#ifndef __MOD_MATRIX
#define __MOD_MATRIX

#include <type_traits>
#include <utility>
#include <cmath>
#include <cstring>
#include <cstdint>

template<typename _type> concept arithmetric = requires (_type Arth, int i) {
    Arth + Arth;                                    // addition 
    Arth += Arth;
    Arth - Arth;                                    // substraction 
    Arth -= Arth;
    Arth * Arth;                                    // multiplication 
    Arth *= Arth;
    Arth / Arth;                                    // division 
    Arth /= Arth;
    Arth == Arth;                                   // equal comparation
    Arth = Arth;                                    // asignation
    requires std::constructible_from<_type, int>;   // 1, -1, 0 needs to be convertible to _type
};

/**********************
 *    Generic type    *
 **********************/

template<arithmetric T>
class Matrix{
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
