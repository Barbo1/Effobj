#pragma once

#include "./needed.hpp"
#include <array>
#include <xmmintrin.h>

/********************************
 *    Fixed Size, Float type    *
 ********************************/

class Matrix4 {
  private:
    std::array<fv_x4, 4> _data_;

  public:
    Matrix4 ();
    Matrix4 (float * data_);
    Matrix4 (fv_x4 * data_);
    Matrix4 (const Matrix4 & A);
    Matrix4 operator= (const Matrix4 & A);
    ~Matrix4 ();

    float operator() (unsigned row, unsigned column) const;

    void changer (unsigned row1, unsigned row2);
    void changec (unsigned col1, unsigned col2);

    void multr (unsigned row, float multiplier);
    void multc (unsigned col, float multiplier);

    Matrix4 operator+ (const Matrix4& A);
    Matrix4 operator* (float multiplier);
    Matrix4 operator* (const Matrix4& A);

    Matrix4 traspose ();
    float determinant ();
    Matrix4 invert ();
};
