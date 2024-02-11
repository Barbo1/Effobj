#include <iostream>
#include <string>
#include "../../../matrix.hpp"

template <arithmetric T>
void printM (Matrix<T> M) {
    int rows = M.rows();
    int cols = M.cols();
    std::cout << std::endl;
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            std::cout << M(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

void print (std::string str) {
    std::cout << std::endl << str << std::endl;
}

int main () {
    Matrix<bool> b = Matrix<bool> (3, 4, new bool[12]{
        1, 1, 0, 1,
        0, 1, 0, 0,
        1, 0, 1, 0 
    }, true);

    print ("showing b: ");
    printM(b);
    Matrix<bool> c = Matrix<bool> (3, 4, new bool[12]{
        0, 1, 0, 1,
        1, 0, 1, 0,
        1, 0, 0, 0 
    }, true);
    print ("showing c: ");
    printM(c);

    print ("change columns 1 and 4: ");
    c.changec(1, 4);
    printM(c);
    print ("change rows 1 and 2: ");
    c.changer(1, 2);
    printM(c);

    Matrix<bool> d = Matrix<bool> (12, 11, new bool[132]{
        0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0,
        1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1,
        1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1,
        1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1,
        0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1,
        0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1,
        1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0,
        0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0,
        0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0
    }, true);

    print ("showing d: ");
    printM (d);
    print ("change columns 1 and 11: ");
    d.changec(1, 11);
    printM(d);
    print ("change rows 1 and 3: ");
    d.changer(1, 3);
    printM(d);

    print ("showing c: ");
    printM (c);
    print ("showing b: ");
    printM (b);
    print ("showing b + c: ");
    printM (b + c);
    print ("showing traspose of c: ");
    printM (c.traspose());
    print ("showing b by traspose of c: ");
    printM (b * c.traspose());

    print ("showing b by true and false: ");
    printM (b * true);
    printM (b * false);
    
    print ("showing d: ");
    printM (d);
    print ("showing traspose of d: ");
    printM (d.traspose());

    Matrix<bool> r = Matrix<bool> (8, 8, new bool[64] {
        1, 1, 1, 1, 0, 0, 1, 1,
        0, 1, 1, 1, 0, 0, 1, 1,
        0, 0, 1, 1, 0, 0, 1, 1,
        0, 0, 0, 1, 0, 1, 1, 1,
        0, 0, 0, 0, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 1    
    }, true);
    print ("showing r: ");
    printM (r);
    print ("showing traspose of r: ");
    printM (r.traspose());
    print ("showing r attached in (5, 2): ");
    printM (r.attached(5, 2));

    Matrix<bool> q = Matrix<bool> (9, 9, new bool[81] {
        1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 0, 0, 1, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 0,
        0, 1, 0, 1, 1, 1, 1, 0, 0,
        1, 1, 0, 0, 1, 1, 0, 1, 1,
        0, 1, 1, 0, 0, 1, 0, 1, 0,
        0, 0, 0, 1, 0, 0, 0, 1, 0,
        0, 1, 1, 0, 1, 0, 0, 0, 0,
        1, 0, 1, 0, 1, 1, 0, 1, 0,
    }, true);
    print ("showing q: ");
    printM (q);
    print ("showing q attached in (9, 9): ");
    printM (q.attached(9, 9));
    
    print ("showing d: ");
    printM (d);
    print ("showing d attached in (8, 10): ");
    printM (d.attached(8, 10));
    print ("showing d with row 8 multiplied by true: ");
    d.multr(8, true);
    printM (d);
    print ("showing d with row 8 multiplied by false: ");
    d.multr(8, false);
    printM (d);
    print ("showing d with columns 6 multiplied by true: ");
    d.multc(6, true);
    printM (d);
    print ("showing d with columns 6 multiplied by false: ");
    d.multc(6, false);
    printM (d);

    Matrix<int> a = r.cast<int>();
    print ("matrix bool casted to int by 2: ");
    printM(a + a);

    Matrix<bool> t = Matrix<bool> (9, 5);
    print ("showing matrix t: ");
    printM (t);
    print ("setting 1 in diagonal: ");
    t.set (1, 1);
    t.set (2, 2);
    t.set (3, 3);
    t.set (4, 4);
    t.set (5, 5);
    printM (t);
    
    Matrix<bool> a1 = Matrix<bool> (3, 4, new bool[12]{
        0, 0, 1, 0,
        0, 1, 1, 0,
        1, 0, 0, 1 
    }, true);
    
    Matrix<bool> a2 = Matrix<bool> (4, 4, new bool[16]{
        0, 0, 1, 0,
        1, 1, 0, 1,
        0, 1, 1, 0,
        1, 0, 0, 0 
    }, true);

    print ("showing a1: ");
    printM (a1);
    print ("showing a2: ");
    printM (a2);
    print ("showing a1 * a2: ");
    printM (a1 * a2);
    
    Matrix<bool> y = Matrix<bool> (10, 12, new bool[120] {
        0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1,
        0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1,
        0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0,
        1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1,
        0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1,
        1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1,
        1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0,
        1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0
    }, true);

    print ("showing y: ");
    printM (y);
    print ("showing q: ");
    printM (a2);
    print ("showing q * y: ");
    printM (q * y.attached(10, 12));

    return 0;
}
