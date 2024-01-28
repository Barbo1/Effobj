#include "../xpres.hpp"
#include "../matrix.hpp"

void print_matrix(const Matrix<Xpres> & M) {
    if(!M.is_null()) {
        std::cout << M(1,1) << " " << M(1,2) << std::endl;
        std::cout << M(2,1) << " " << M(2,2) << std::endl;
    } else {
        std::cout << "es nula" << std::endl;
    }
}

int main () {
    Xpres * arr = new Xpres[4]{
        "a"_exp , "b"_exp
        "c"_exp , "d"_exp
    }
    Matrix<Xpres> M1 = Matrix<Xpres>(2, 2, arr);
    
    arr = new Xpres[4]{
        "e"_exp , "f"_exp
        "g"_exp , "h"_exp
    }
    Matrix<Xpres> M2 = Matrix<Xpres>(2, 2, arr);

    print_matrix (M2*M1);
}
