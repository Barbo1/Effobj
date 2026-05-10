#include <iostream>
#include <string>

#include "../xpres.hpp"
#include "../matrix.hpp"

template<typename T>
void print_matrix(const Matrix<T> & A){
    unsigned col = A.cols();
    unsigned row = A.rows();
    for (unsigned i = 1; i <= row; i++) {
        for (unsigned j = 1; j <= row; j++) {
            std::cout << A(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

void print_this(std::pair<char, void*> a) {
    switch (a.first) {
        case 'i':
            std::cout << *((long int *)a.second) << std::endl;
            delete (long int*) a.second;
            break;
        case 'd':
            std::cout << * ((double *)a.second) << std::endl;
            delete (double*) a.second;
            break;
        case 'm':
            print_matrix(*(Matrix<long int> *) a.second);
            delete (Matrix<long int> *) a.second;
            break;
        case 'M':
            print_matrix(*(Matrix<double> *) a.second);
            delete (Matrix<double> *) a.second;
            break;
        case 'e':
            std::cout << *((Xpres *)a.second) << std::endl;
            delete (Xpres *) a.second;
            break;
        default:
            break;
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "prueba de compose: x*r*r + q*x*r" << std::endl;
    Xpres xp5 = "x*r*r + q*x*r"_exp;
    Xpres::iterator it5 = Xpres::iterator (xp5).compose(0, 1, "x");
    it5[1].compose(0, 1, "r");
    std::cout << it5 << std::endl;
}
