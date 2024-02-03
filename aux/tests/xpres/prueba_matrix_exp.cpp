#include <iostream>

#include "../../../xpres.hpp"
#include "../../../matrix.hpp"

template<typename T>
void print_matrix(Matrix<T> M) {
    if(!M.is_null()) {
        for (unsigned r = 1;r <= M.rows();r++) {
            for (unsigned c = 1; c <= M.cols(); c++) {
                std::cout << M(r, c) << "  ";
            }
            std::cout << std::endl;
        }
    } else {
        std::cout << "es nula" << std::endl;
    }
}

int main () {
    std::cout << (std::is_floating_point_v<Xpres>) << std::endl;
    std::cout << (std::is_integral_v<Xpres>) << std::endl;

    Matrix<Xpres> M1 = Matrix<Xpres>(2, 2, new Xpres[4]{
        "a"_exp , "b"_exp,
        "c"_exp , "d"_exp
    }, true);
    
    Matrix<Xpres> M2 = Matrix<Xpres>(2, 2, new Xpres[4]{
        "e"_exp , "f"_exp,
        "g"_exp , "h"_exp
    }, true);
   
    std::cout << "matrix 1: " << std::endl;
    print_matrix <Xpres>(M1);

    std::cout << std::endl;
    std::cout << "matrix 2: " << std::endl;
    print_matrix <Xpres>(M2);

    std::cout << std::endl;
    std::cout << "multiplication: " << std::endl;
    print_matrix <Xpres>(M1 * M2);

    std::cout << std::endl;
    std::cout << "multiplication by constant: " << std::endl;
    print_matrix <Xpres>(M1 * "!r"_exp);

    std::cout << std::endl;
    std::cout << "addition: " << std::endl;
    print_matrix <Xpres>(M1 + M2);

    Xpres exp = M1.determinant();

    std::cout << std::endl;
    std::cout << "determinant 1: " << exp << std::endl;
    std::cout << "determinant 2: " << M2.determinant() << std::endl;

    Xpres::iterator(exp).descompose(2, 1);
    std::cout << exp << std::endl;
   
    std::cout << std::endl;
    std::cout << "inverse 1: " << std::endl;
    print_matrix <Xpres>(M1.invert());
    std::cout << "determinant 2: " << std::endl;
    print_matrix <Xpres>(M2.invert());
}
