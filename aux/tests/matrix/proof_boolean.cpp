#include <iostream>
#include "../../../matrix.hpp"

int main () {
    Matrix<bool> b = Matrix (3, 3, new bool[9]{
        true, true, false,
        false, true, false,
        true, false, true
    }, true);


    return 0;
}
