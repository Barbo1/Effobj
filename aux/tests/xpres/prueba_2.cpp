#include <iostream>
#include "./fix_matrix_d.hpp"

void print_matrix(const Matrix4 & M) {
    if(!M.is_null()) {
        std::cout << M(1,1) << " " << M(1,2) << " " << M(1,3) << " " << M(1,4) << std::endl;
        std::cout << M(2,1) << " " << M(2,2) << " " << M(2,3) << " " << M(2,4) << std::endl;
        std::cout << M(3,1) << " " << M(3,2) << " " << M(3,3) << " " << M(3,4) << std::endl;
        std::cout << M(4,1) << " " << M(4,2) << " " << M(4,3) << " " << M(4,4) << std::endl;
    } else {
        std::cout << "es nula" << std::endl;
    }
}

int main() {
    float * arr = new float[16]{
                          1,  2,  3,  4,
                         13, -2, 15,  7,
                        -10,  1, -6, -1,
                          7, 14,  2, -3};
    Matrix4 A = Matrix(arr);

    arr = new float[16]{
                      4, 40, -3,  6,
                      1,  1, -1,  5,
                      8, 13,  4, 44,
                    -11, -2,  3,  3};
    Matrix4 B = Matrix(arr);
    
    arr = new float[16]{
                    20,   1, -13,  -3,
                    23,  44,   5,  85,
                     1,   1,   3, -19,
                     4, -23, -12, -1};
    Matrix4 C = Matrix(arr);

    std::cout << "suma de matrices: " << std::endl;
    print_matrix(A);
    std::cout << "+" << std::endl;
    print_matrix(B);
    std::cout << "=" << std::endl;
    print_matrix(A+B);
    std::cout << std::endl << std::endl;

    std::cout << "multiplicacion de matrices: " << std::endl;
    print_matrix(A);
    std::cout << "*" << std::endl;
    print_matrix(B);
    std::cout << "=" << std::endl;
    print_matrix(A*B);
    std::cout << std::endl << std::endl;

    print_matrix(A);
    std::cout << "multiplico la columna 2 por -2: " << std::endl;
    A.multc(2, -2);
    print_matrix(A);
    std::cout << "multiplico la fila 1 por 1.5: " << std::endl;
    A.multr(1, 1.5);
    print_matrix(A);
    std::cout << "multiplico la columna 3 por 5.1: " << std::endl;
    A.multc(3, 5.1);
    print_matrix(A);

    std::cout << "cambio la fila 2 por 1: " << std::endl;
    A.changer(2, 1);
    print_matrix(A);
    std::cout << "cambio la fila 3 por 1: " << std::endl;
    A.changer(3, 1);
    print_matrix(A);
    std::cout << "cambio la columna 2 por 1: " << std::endl;
    A.changec(2, 1);
    print_matrix(A);
    std::cout << "cambio la columna 1 por 3: " << std::endl;
    A.changec(1, 3);
    print_matrix(A);
    std::cout << std::endl << std::endl;

    std::cout << "transpuesta de una matriz:" << std::endl;
    print_matrix(A);
    std::cout << "traspuesta:" << std::endl;
    print_matrix(A.traspose());
    std::cout << std::endl << std::endl;

    std::cout << "determinante de matrices: " << std::endl;
    std::cout << " |A| = " << A.determinant() << std::endl;
    std::cout << " |B| = " << B.determinant() << std::endl;
    std::cout << " |C| = " << C.determinant() << std::endl;
    std::cout << std::endl << std::endl;
   
    std::cout << "inversa de matrices: " << std::endl;
    std::cout << " A^(-1) = " << std::endl;
    print_matrix(A.invert()); 
    std::cout << std::endl << "prueba de que esta bien:" << std::endl;
    print_matrix(A*A.invert());
    std::cout << std::endl << std::endl;
    std::cout << " B^(-1) = " << std::endl;
    print_matrix(B.invert());
    std::cout << std::endl << "prueba de que esta bien:" << std::endl;
    print_matrix(B*B.invert());
    std::cout << std::endl << std::endl;
    std::cout << " C^(-1) = " << std::endl;
    print_matrix(C.invert()); 
    std::cout << std::endl << "prueba de que esta bien:" << std::endl;
    print_matrix(C*C.invert());
    std::cout << std::endl << std::endl;    
}
