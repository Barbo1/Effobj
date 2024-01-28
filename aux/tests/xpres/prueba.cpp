#include <iostream>
#include <cstdlib>
#include <chrono>
#include "matrix.hpp"

void printMatrix(Matrix<float> A) {
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

int main() {
    using namespace std::chrono;

    unsigned i, j;
    unsigned n;
    unsigned t;
    float * a;
    
    float * elem = new float[4]{0.5, 0.5,
                                (float)1/3, (float)2/3};
    Matrix<float> A = Matrix<float>(2, 2, elem);

    elem = new float[9]{14, 2, -4,
                          19, 6, -2,
                          12, 2, -3};
    Matrix<float> B = Matrix<float>(3, 3, elem);
    
    elem = new float[16]{-3,  2 ,-1, -2,
                           1 ,-1,  1,  1,
                          -2,  1 ,-1, -1,
                           1,  0,  0,  1};
    Matrix<float> C = Matrix<float>(4, 4, elem);

    elem = new float[9]{ 3, -4, -3,
                          -1,  2,  7,
                          -2,  4,  1};
    Matrix<float> D = Matrix<float>(3, 3, elem);
   
    elem = new float[9]{ 1, -2, -7,
                          -1,  2,  7,
                          -2,  4,  1};
    Matrix<float> U = Matrix<float>(3, 3, elem);
   
    elem = new float[27]{ 3, -4, -3, 14,  3,  51, 8, 26, 2, 
                         -1,  2,  7,  3, 42, 111, 2,  4, 7,
                         -2,  4,  1, 44,  8,  21, 4,  4, 4};
    Matrix<float> T2 = Matrix<float>(3, 9, elem);
    
    elem = new float[27]{  5, -31,  -8,  
                          38, 333, 434,   
                           5,   1,  43, 
                         -32,  53,   7,
                         -72,  43,   6,  
                          37, -83,   5,
                          24,   5,  71,  
                          45, -32, -22, 
                         -26, -63,  35};
    Matrix<float> T1 = Matrix<float>(9, 3, elem);

    printMatrix(A);
    std::cout << std::endl;
    printMatrix(B);
    std::cout << std::endl;
    printMatrix(C);
    std::cout << std::endl;
    printMatrix(D);
    std::cout << std::endl;

    Matrix F = mfo(4, 4, (float)1.5);
    printMatrix(F);
    std::cout << std::endl;
    Matrix G = identity<float>(5);
    G = identity<float>(5);
    printMatrix(G);

    std::cout << std::endl;
    std::cout << G.is_stochastic() << std::endl;
    std::cout << A.is_stochastic() << std::endl;
    std::cout << B.is_stochastic() << std::endl;
    std::cout << "-*----------" << std::endl;
    printMatrix(B);
    B.changec(1, 3);
    std::cout << "-*---c-1-3-----" << std::endl;
    printMatrix(B);
    B.changer(2, 3);
    std::cout << "-*---r-2-3-----" << std::endl;
    printMatrix(B);
    B.multr(2, -2);
    std::cout << "-*----mult-(-2)-columna-2---" << std::endl;
    printMatrix(B);
    B.multr(1, 1.5);
    std::cout << "-*----mult-1.5-fila-1---" << std::endl;
    printMatrix(B);
    B.multr(3, 10);
    std::cout << "-*----mult-10-fila-3---" << std::endl;
    printMatrix(B);
    B.changer(2, 3);
    std::cout << "-*---r-2-3-----" << std::endl;
    printMatrix(B);
    
    std::cout << std::endl << "sumo T1 traspuesta y T2" << std::endl;
    printMatrix(T1.traspose());
    std::cout << "+" << std::endl;
    printMatrix(T2);
    std::cout << "=" << std::endl;
    printMatrix(T1.traspose()+T2);

    std::cout << std::endl << "multiplico matriz T1 por 1.5:" << std::endl;
    printMatrix(T1 * 1.5);
    std::cout << std::endl << "traspuesta de T1:" << std::endl;
    printMatrix(T1.traspose());

    std::cout << std::endl << "muestro B:" << std::endl;
    printMatrix(B);
    std::cout << std::endl << "attached de B en (1, 1):" << std::endl;
    printMatrix(B.attached(1,1));
    std::cout << std::endl << "attached de B en (2, 2):" << std::endl;
    printMatrix(B.attached(2,2));
    std::cout << std::endl << "attached de B en (3, 1):" << std::endl;
    printMatrix(B.attached(3,1));

    std::cout << std::endl;
    printMatrix(T2);
    std::cout << "*" << std::endl;
    printMatrix(T1);
    std::cout << "=" << std::endl; 
    printMatrix(T2*T1);
    
    std::cout << std::endl << "|B| = " << B.determinant()<< ", donde B = " << std::endl;
    printMatrix(B);
    std::cout << std::endl << "|D| = " << D.determinant()<< ", donde D = " << std::endl;
    printMatrix(D);
    std::cout << std::endl << "|G| = " << G.determinant()<< ", donde G = " << std::endl;
    printMatrix(G);
    std::cout << std::endl << "|U| = " << U.determinant()<< ", donde H = " << std::endl;
    printMatrix(U);
    
    std::cout << std::endl << "inversa de D:" << std::endl;
    Matrix<float> inv = D.invert();
    printMatrix(inv);
    std::cout << "------------" << std::endl;
    printMatrix(inv*D);
    
    /*
    inv = D.invert();
    printMatrix(inv);
    std::cout << "------------" << std::endl;
    printMatrix(inv*D);
    std::cout << std::endl;
    
    printMatrix(C);
    Matrix ATT = C.attached(3,4);
    std::cout << "------------" << std::endl;
    printMatrix(ATT);

    i = 3;
    j = 3;
    bool * elem_b = new bool[i*j]{true, true, false,
                                     false, true, false,
                                     true, false, true};
    Matrix<bool> R = Matrix<bool>(i, j, elem_b);
    i = 3;
    j = 3;
    elem_b = new bool[i*j]{true, false, true,
                                     false, true, false,
                                     true, false, true};
    Matrix<bool> M = Matrix<bool>(i, j, elem_b);
    */
    /*
    std::cout << "multiplicacion:" << std::endl;
    printMatrix(R);
    std::cout << "*" << std::endl;
    printMatrix(M);
    std::cout << "*" << std::endl;
    printMatrix(R*M);
    std::cout << std::endl;
    */

    /*
    printMatrix(R);
    std::cout << "-----traspuersta-----" << std::endl;
    printMatrix(R.traspose());
    std::cout << "-----multiplicacion-por-la-traspuesta-----" << std::endl;
    //printMatrix(R*R.traspose());
    */
}
