#include <immintrin.h>
#include <utility>
#include "./fix_matrix_d.hpp"

union fv_x44 {
    __m128 _v;
    float _f[4];
};

Matrix4::Matrix4() {
    _data_ = nullptr;
}

Matrix4::Matrix4(float * data_) {
    _data_ = new fv_x44[4];

    _data_[0]._f[0] = data_[0];
    _data_[0]._f[1] = data_[1];
    _data_[0]._f[2] = data_[2];
    _data_[0]._f[3] = data_[3];
    
    _data_[1]._f[0] = data_[4];
    _data_[1]._f[1] = data_[5];
    _data_[1]._f[2] = data_[6];
    _data_[1]._f[3] = data_[7];
    
    _data_[2]._f[0] = data_[8];
    _data_[2]._f[1] = data_[9];
    _data_[2]._f[2] = data_[10];
    _data_[2]._f[3] = data_[11];
    
    _data_[3]._f[0] = data_[12];
    _data_[3]._f[1] = data_[13];
    _data_[3]._f[2] = data_[14];
    _data_[3]._f[3] = data_[15];

    delete [] data_;
}


Matrix4::Matrix4(fv_x44 * data_) {
    _data_ = data_;
}

Matrix4::Matrix4(const Matrix4 & A) {
    _data_[0]._v = A._data_[0]._v;
    _data_[1]._v = A._data_[1]._v;
    _data_[2]._v = A._data_[2]._v;
    _data_[3]._v = A._data_[3]._v;
}

Matrix4::Matrix4(Matrix4 && A) {
    _data_ = A._data_;
    A._data_ = nullptr;
}

Matrix4 Matrix4::operator=(const Matrix4 & A) {
    delete [] _data_;
    _data_[0]._v = A._data_[0]._v;
    _data_[1]._v = A._data_[1]._v;
    _data_[2]._v = A._data_[2]._v;
    _data_[3]._v = A._data_[3]._v;
    return *this;
}

Matrix4 Matrix4::operator=(Matrix4 && A) {
    delete [] _data_;
    _data_ = A._data_;
    A._data_ = nullptr;
    return *this;
}

Matrix4::~Matrix4() {
    if(_data_ != nullptr) {
        delete [] _data_;
    }
}

float Matrix4::operator()(unsigned row, unsigned column) const {
    row--;
    column--;
    if(row < 4 && column < 4) {
        return _data_[row]._f[column];
    }
    return 0;
}

void Matrix4::changec(unsigned col1, unsigned col2) {
    col1--;
    col2--;
    if(col1 < 4 && col2 < 4 && col1 != col2) {
        std::swap(_data_[0]._f[col1], _data_[0]._f[col2]);
        std::swap(_data_[1]._f[col1], _data_[1]._f[col2]);
        std::swap(_data_[2]._f[col1], _data_[2]._f[col2]);
        std::swap(_data_[3]._f[col1], _data_[3]._f[col2]);
    }
}

void Matrix4::changer(unsigned row1, unsigned row2) {
    row1--;
    row2--;
    if(row1 < 4 && row2 < 4 && row1 != row2) {
        std::swap(_data_[row1]._v, _data_[row2]._v);
    }
}

void Matrix4::multc(unsigned col, float multiplier) {
    col--;
    if(col < 4) {
        _data_[0]._f[col] *= multiplier;
        _data_[1]._f[col] *= multiplier;
        _data_[2]._f[col] *= multiplier;
        _data_[3]._f[col] *= multiplier;
    }
}

void Matrix4::multr(unsigned row, float multiplier) {
    row--;
    if(row < 4) {
        _data_[row]._v = _mm_mul_ps(_data_[row]._v, _mm_set1_ps(multiplier));
    }
}

bool Matrix4::is_null() const {
    return _data_ == nullptr;
}

Matrix4 Matrix4::operator+(const Matrix4 & A) {
    fv_x44 * data = new fv_x44[4];
    data[0]._v = _mm_add_ps(_data_[0]._v, A._data_[0]._v);
    data[1]._v = _mm_add_ps(_data_[1]._v, A._data_[1]._v);
    data[2]._v = _mm_add_ps(_data_[2]._v, A._data_[2]._v);
    data[3]._v = _mm_add_ps(_data_[3]._v, A._data_[3]._v);
    return Matrix4(data);
}

Matrix4 Matrix4::operator*(const Matrix4 & A) {
    fv_x44 * _data_new_  = new fv_x44[4];
    fv_x44 * _tras_ = new fv_x44[4];
    fv_x44 res;

    // create traspose matrix.
    _tras_[0]._f[0] = A._data_[0]._f[0];
    _tras_[0]._f[1] = A._data_[1]._f[0];
    _tras_[0]._f[2] = A._data_[2]._f[0];
    _tras_[0]._f[3] = A._data_[3]._f[0];

    _tras_[1]._f[0] = A._data_[0]._f[1];
    _tras_[1]._f[1] = A._data_[1]._f[1];
    _tras_[1]._f[2] = A._data_[2]._f[1];
    _tras_[1]._f[3] = A._data_[3]._f[1];

    _tras_[2]._f[0] = A._data_[0]._f[2];
    _tras_[2]._f[1] = A._data_[1]._f[2];
    _tras_[2]._f[2] = A._data_[2]._f[2];
    _tras_[2]._f[3] = A._data_[3]._f[2];

    _tras_[3]._f[0] = A._data_[0]._f[3];
    _tras_[3]._f[1] = A._data_[1]._f[3];
    _tras_[3]._f[2] = A._data_[2]._f[3];
    _tras_[3]._f[3] = A._data_[3]._f[3];

    // do the multipication.
    // row 1
    res._v = _mm_mul_ps(_data_[0]._v, _tras_[0]._v);
    _data_new_[0]._f[0] = res._f[0] + res._f[1] + res._f[2] + res._f[3];
    
    res._v = _mm_mul_ps(_data_[0]._v, _tras_[1]._v);
    _data_new_[0]._f[1] = res._f[0] + res._f[1] + res._f[2] + res._f[3];
    
    res._v = _mm_mul_ps(_data_[0]._v, _tras_[2]._v);
    _data_new_[0]._f[2] = res._f[0] + res._f[1] + res._f[2] + res._f[3];
    
    res._v = _mm_mul_ps(_data_[0]._v, _tras_[3]._v);
    _data_new_[0]._f[3] = res._f[0] + res._f[1] + res._f[2] + res._f[3];
    
    // row 2
    res._v = _mm_mul_ps(_data_[1]._v, _tras_[0]._v);
    _data_new_[1]._f[0] = res._f[0] + res._f[1] + res._f[2] + res._f[3];
    
    res._v = _mm_mul_ps(_data_[1]._v, _tras_[1]._v);
    _data_new_[1]._f[1] = res._f[0] + res._f[1] + res._f[2] + res._f[3];
    
    res._v = _mm_mul_ps(_data_[1]._v, _tras_[2]._v);
    _data_new_[1]._f[2] = res._f[0] + res._f[1] + res._f[2] + res._f[3];
    
    res._v = _mm_mul_ps(_data_[1]._v, _tras_[3]._v);
    _data_new_[1]._f[3] = res._f[0] + res._f[1] + res._f[2] + res._f[3];
    
    // row 3
    res._v = _mm_mul_ps(_data_[2]._v, _tras_[0]._v);
    _data_new_[2]._f[0] = res._f[0] + res._f[1] + res._f[2] + res._f[3];
    
    res._v = _mm_mul_ps(_data_[2]._v, _tras_[1]._v);
    _data_new_[2]._f[1] = res._f[0] + res._f[1] + res._f[2] + res._f[3];
    
    res._v = _mm_mul_ps(_data_[2]._v, _tras_[2]._v);
    _data_new_[2]._f[2] = res._f[0] + res._f[1] + res._f[2] + res._f[3];
    
    res._v = _mm_mul_ps(_data_[2]._v, _tras_[3]._v);
    _data_new_[2]._f[3] = res._f[0] + res._f[1] + res._f[2] + res._f[3];
    
    // row 4 
    res._v = _mm_mul_ps(_data_[3]._v, _tras_[0]._v);
    _data_new_[3]._f[0] = res._f[0] + res._f[1] + res._f[2] + res._f[3];
    
    res._v = _mm_mul_ps(_data_[3]._v, _tras_[1]._v);
    _data_new_[3]._f[1] = res._f[0] + res._f[1] + res._f[2] + res._f[3];
    
    res._v = _mm_mul_ps(_data_[3]._v, _tras_[2]._v);
    _data_new_[3]._f[2] = res._f[0] + res._f[1] + res._f[2] + res._f[3];
    
    res._v = _mm_mul_ps(_data_[3]._v, _tras_[3]._v);
    _data_new_[3]._f[3] = res._f[0] + res._f[1] + res._f[2] + res._f[3];
    
    // return.
    delete [] _tras_;
    return Matrix4(_data_new_);
}

Matrix4 Matrix4::operator*(float multiplier) {
    fv_x44 * data = new fv_x44[4];
    __m128 res = _mm_set1_ps(multiplier);
    
    data[0]._v = _mm_mul_ps(res, _data_[0]._v);
    data[1]._v = _mm_mul_ps(res, _data_[1]._v);
    data[2]._v = _mm_mul_ps(res, _data_[2]._v);
    data[3]._v = _mm_mul_ps(res, _data_[3]._v);

    return Matrix4(data);
}

Matrix4 Matrix4::traspose() {
    fv_x44 * _data_new_ = new fv_x44[4];
    
    _data_new_[0]._f[0] = _data_[0]._f[0];
    _data_new_[0]._f[1] = _data_[1]._f[0];
    _data_new_[0]._f[2] = _data_[2]._f[0];
    _data_new_[0]._f[3] = _data_[3]._f[0];
    
    _data_new_[1]._f[0] = _data_[0]._f[1];
    _data_new_[1]._f[1] = _data_[1]._f[1];
    _data_new_[1]._f[2] = _data_[2]._f[1];
    _data_new_[1]._f[3] = _data_[3]._f[1];
    
    _data_new_[2]._f[0] = _data_[0]._f[2];
    _data_new_[2]._f[1] = _data_[1]._f[2];
    _data_new_[2]._f[2] = _data_[2]._f[2];
    _data_new_[2]._f[3] = _data_[3]._f[2];
    
    _data_new_[3]._f[0] = _data_[0]._f[3];
    _data_new_[3]._f[1] = _data_[1]._f[3];
    _data_new_[3]._f[2] = _data_[2]._f[3];
    _data_new_[3]._f[3] = _data_[3]._f[3];

    return Matrix4(_data_new_);
}

float Matrix4::determinant() { 
    fv_x44 * _data_new_ = new fv_x44[4];
    __m128 zero = _mm_setzero_ps();
    float determinant = 1;
    float cm_1, cm_2;

    _data_new_[0]._v = _data_[0]._v;
    _data_new_[1]._v = _data_[1]._v;
    _data_new_[2]._v = _data_[2]._v;
    _data_new_[3]._v = _data_[3]._v;

    /*--------------iteration-1----------------*/

    if(_data_new_[0]._f[0] == 0) {
        if(_data_new_[1]._f[0] != 0) {
            std::swap(_data_new_[1]._v, _data_new_[0]._v);
            determinant *= -1;
        } else if(_data_[2]._f[0] != 0) {
            std::swap(_data_new_[2]._v, _data_new_[0]._v);
            determinant *= -1;
        } else if(_data_new_[3]._f[0] != 0) {
            std::swap(_data_new_[3]._v, _data_new_[0]._v);
            determinant *= -1;
        } else {
            delete [] _data_new_;
            return 0;
        }
    }

    cm_1 = 1/_data_new_[0]._f[0];
    if((cm_2 = _data_new_[1]._f[0]) != 0) {
        cm_2 *= cm_1;
        _data_new_[1]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _data_new_[0]._v, _data_new_[1]._v);
    }
    if((cm_2 = _data_new_[2]._f[0]) != 0) {
        cm_2 *= cm_1;
        _data_new_[2]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _data_new_[0]._v, _data_new_[2]._v);
    }
    if((cm_2 = _data_new_[3]._f[0]) != 0) {
        cm_2 *= cm_1;
        _data_new_[3]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _data_new_[0]._v, _data_new_[3]._v);
    }

    determinant *= _data_new_[0]._f[0];
   
    /*--------------iteration-2----------------*/

    if(_data_new_[1]._f[1] == 0) {
        if(_data_new_[2]._f[1] != 0) {
            std::swap(_data_new_[2]._v, _data_new_[1]._v);
            determinant *= -1;
        } else if(_data_[3]._f[1] != 0) {
            std::swap(_data_new_[3]._v, _data_new_[1]._v);
            determinant *= -1;
        } else {
            delete [] _data_new_;
            return 0;
        }
    }

    cm_1 = 1/_data_new_[1]._f[1];
    if((cm_2 = _data_new_[2]._f[1]) != 0) {
        cm_2 *= cm_1;
        _data_new_[2]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _data_new_[1]._v, _data_new_[2]._v);
    }
    if((cm_2 = _data_new_[3]._f[1]) != 0) {
        cm_2 *= cm_1;
        _data_new_[3]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _data_new_[1]._v, _data_new_[3]._v);
    }
   
    determinant *= _data_new_[1]._f[1];

    /*--------------iteration-3----------------*/

    if(_data_new_[2]._f[2] == 0) {
        if(_data_new_[3]._f[2] != 0) {
            std::swap(_data_new_[3]._v, _data_new_[2]._v);
            determinant *= -1;
        } else {
            delete [] _data_new_;
            return 0;
        }
    }

    cm_1 = _data_new_[2]._f[2];
    if((cm_2 = _data_new_[3]._f[2]) != 0) {
        cm_2 /= cm_1;
        _data_new_[3]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _data_new_[2]._v, _data_new_[3]._v);
    }
    
    determinant *= cm_1;

    /*------------------------------*/

    determinant *= _data_new_[3]._f[3];
    delete [] _data_new_;
    return determinant;
}

Matrix4 Matrix4::invert() {
    fv_x44 * _data_new_ = new fv_x44[4];
    fv_x44 * _iden_ = new fv_x44[4];
    __m128 zero = _mm_setzero_ps(), res;
    float cm_1, cm_2;

    _data_new_[0]._v = _data_[0]._v;
    _data_new_[1]._v = _data_[1]._v;
    _data_new_[2]._v = _data_[2]._v;
    _data_new_[3]._v = _data_[3]._v;
                      
    _iden_[0]._v = _iden_[1]._v = _iden_[2]._v = _iden_[3]._v = zero;
    _iden_[0]._f[0] = _iden_[1]._f[1] = _iden_[2]._f[2] = _iden_[3]._f[3] = 1;
    
    /*--------------iteration-1----------------*/

    if(_data_new_[0]._f[0] == 0) {
        if(_data_new_[1]._f[0] != 0) {
            std::swap(_data_new_[1]._v, _data_new_[0]._v);
            std::swap(_iden_[1]._v, _iden_[0]._v);
        } else if(_data_new_[2]._f[0] != 0) {
            std::swap(_data_new_[2]._v, _data_new_[0]._v);
            std::swap(_iden_[2]._v, _iden_[0]._v);
        } else if(_data_new_[3]._f[0] != 0) {
            std::swap(_data_new_[3]._v, _data_new_[0]._v);
            std::swap(_iden_[3]._v, _iden_[0]._v);
        } else {
            delete [] _data_new_;
            delete [] _iden_;
            return Matrix4();
        }
    }

    cm_1 = 1/_data_new_[0]._f[0];

    if((cm_2 = _data_new_[1]._f[0]) != 0) {
        cm_2 *= cm_1;
        res = _mm_set1_ps(cm_2);
        _data_new_[1]._v = _mm_fnmadd_ps(res, _data_new_[0]._v, _data_new_[1]._v);
        _iden_[1]._v = _mm_fnmadd_ps(res, _iden_[0]._v, _iden_[1]._v);
    }
    if((cm_2 = _data_new_[2]._f[0]) != 0) {
        cm_2 *= cm_1;
        res = _mm_set1_ps(cm_2);
        _data_new_[2]._v = _mm_fnmadd_ps(res, _data_new_[0]._v, _data_new_[2]._v);
        _iden_[2]._v = _mm_fnmadd_ps(res, _iden_[0]._v, _iden_[2]._v);
    }
    if((cm_2 = _data_new_[3]._f[0]) != 0) {
        cm_2 *= cm_1;
        res = _mm_set1_ps(cm_2);
        _data_new_[3]._v = _mm_fnmadd_ps(res, _data_new_[0]._v, _data_new_[3]._v);
        _iden_[3]._v = _mm_fnmadd_ps(res, _iden_[0]._v, _iden_[3]._v);
    }
   
    /*--------------iteration-2----------------*/

    if(_data_new_[1]._f[1] == 0) {
        if(_data_new_[2]._f[1] != 0) {
            std::swap(_data_new_[2]._v, _data_new_[1]._v);
            std::swap(_iden_[2]._v, _iden_[1]._v);
        } else if(_data_new_[3]._f[1] != 0) {
            std::swap(_data_new_[3]._v, _data_new_[1]._v);
            std::swap(_iden_[3]._v, _iden_[1]._v);
        } else {
            delete [] _data_new_;
            delete [] _iden_;
            return Matrix4();
        }
    }

    cm_1 = 1/_data_new_[1]._f[1];
    
    if((cm_2 = _data_new_[2]._f[1]) != 0) {
        cm_2 *= cm_1;
        res = _mm_set1_ps(cm_2);
        _data_new_[2]._v = _mm_fnmadd_ps(res, _data_new_[1]._v, _data_new_[2]._v);
        _iden_[2]._v = _mm_fnmadd_ps(res, _iden_[1]._v, _iden_[2]._v);
    }
    if((cm_2 = _data_new_[3]._f[1]) != 0) {
        cm_2 *= cm_1;
        res = _mm_set1_ps(cm_2);
        _data_new_[3]._v = _mm_fnmadd_ps(res, _data_new_[1]._v, _data_new_[3]._v);
        _iden_[3]._v = _mm_fnmadd_ps(res, _iden_[1]._v, _iden_[3]._v);
    }
   
    /*--------------iteration-3----------------*/

    if(_data_new_[2]._f[2] == 0) {
        if(_data_new_[3]._f[2] != 0) {
            std::swap(_data_new_[3]._v, _data_new_[2]._v);
            std::swap(_iden_[3]._v, _iden_[2]._v);
        } else {
            delete [] _data_new_;
            delete [] _iden_;
            return Matrix4();
        }
    }

    cm_1 = 1/_data_new_[2]._f[2];
    
    if((cm_2 = _data_new_[3]._f[2]) != 0) {
        cm_2 *= cm_1;
        res = _mm_set1_ps(cm_2);
        _data_new_[3]._v = _mm_fnmadd_ps(res, _data_new_[2]._v, _data_new_[3]._v);
        _iden_[3]._v = _mm_fnmadd_ps(res, _iden_[2]._v, _iden_[3]._v);
    }
    
    /*--------------iteration-4---------------*/

    if(_data_new_[3]._f[3] == 0) {
        delete [] _data_new_;
        delete [] _iden_;
        return Matrix4();
    } 

    /*---------------reverse-iteration-1--------------*/

    cm_1 = 1/_data_new_[3]._f[3];
    res = _mm_set1_ps(cm_1);
    _iden_[3]._v = _mm_mul_ps(res, _iden_[3]._v);
    
    if((cm_2 = _data_new_[2]._f[3]) != 0) {
        _iden_[2]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _iden_[3]._v, _iden_[2]._v);
    }
    if((cm_2 = _data_new_[1]._f[3]) != 0) {
        _iden_[1]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _iden_[3]._v, _iden_[1]._v);
    }
    if((cm_2 = _data_new_[0]._f[3]) != 0) {
        _iden_[0]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _iden_[3]._v, _iden_[0]._v);
    }

    /*---------------reverse-iteration-2--------------*/

    cm_1 = 1/_data_new_[2]._f[2]; 
    res = _mm_set1_ps(cm_1);
    _iden_[2]._v = _mm_mul_ps(res, _iden_[2]._v);
    
    if((cm_2 = _data_new_[1]._f[2]) != 0) {
        _iden_[1]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _iden_[2]._v, _iden_[1]._v);
    }
    if((cm_2 = _data_new_[0]._f[2]) != 0) {
        _iden_[0]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _iden_[2]._v, _iden_[0]._v);
    }

    /*---------------reverse-iteration-3--------------*/
    
    cm_1 = 1/_data_new_[1]._f[1];
    _iden_[1]._v = _mm_mul_ps(_mm_set1_ps(cm_1), _iden_[1]._v);
    
    if((cm_2 = _data_new_[0]._f[1]) != 0) {
        _iden_[0]._v = _mm_fnmadd_ps(_mm_set1_ps(cm_2), _iden_[1]._v, _iden_[0]._v);
    }

    /*---------------reverse-iteration-4--------------*/
    
    _iden_[0]._v = _mm_mul_ps(_mm_set1_ps(1/_data_new_[0]._f[0]), _iden_[0]._v);

    /*---------------return--------------*/

    delete [] _data_new_;
    return Matrix4(_iden_);
}


