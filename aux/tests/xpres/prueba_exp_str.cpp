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
            std::cout << "an error has occur when evaluating." << std::endl;
            break;
    }
    std::cout << std::endl;
}

int main() {
    unsigned i = 0;
    std::cout << "proof of xpres constructor" << std::endl << std::endl;
    std::vector<std::pair<std::string, std::string>> expresiones_{
        std::pair<std::string, std::string> {"!!!2", "!!!2"},
        std::pair<std::string, std::string> {".-.+.2", "0.000000 - 0.000000 + 0.200000"},
        std::pair<std::string, std::string> {"2 + 1.4 + a", "2 + 1.400000 + a"},
        std::pair<std::string, std::string> {"243 + . -2", "243 + 0.000000 - 2"},
        std::pair<std::string, std::string> {"2*3^a", "2 * 3 ^ a"},
        std::pair<std::string, std::string> {"1+!a+1", "1 + !a + 1"},
        std::pair<std::string, std::string> {"1.211 - A*.34 + !12 + !Ni*4 ^ 7 - 1", "1.211000 - A*0.340000 + !12 + !Ni*4 ^ 7 - 1"},
        std::pair<std::string, std::string> {"!~!2", "!(~!2)"},
        std::pair<std::string, std::string> {"!--!-a", "!(--!(-a))"},
        std::pair<std::string, std::string> {"a * (4)^1", "a * 4 ^ 1"},
        std::pair<std::string, std::string> {"q * tan(2 - !13)", "q * tan(2 - !13)"},
        std::pair<std::string, std::string> {"-(-((1)))", "--1"},
        std::pair<std::string, std::string> {"(-!4*.3)*2^.", "(-!4 * 0.300000) * 2 ^ 0.000000"},
        std::pair<std::string, std::string> {"(((1)))", "1"},
        std::pair<std::string, std::string> {"(.-1.|.1)", "0.000000 - 1.000000 | 0.100000"},
        std::pair<std::string, std::string> {"1 + cos(1 + 2)", "1 + cos(1 + 2)"},
        std::pair<std::string, std::string> {"cos(a)", "cos(a)"},
        std::pair<std::string, std::string> {"1.2 | 2.2 < 2 | 14", "1.200000 | 2.200000 < 2 | 14"},
        std::pair<std::string, std::string> {"(1.211 - A*.34 + !12 + !(Ni))*4 ^ (1/7)", "(1.211000 - A*0.340000 + !12 + !(Ni))*4 ^ (1/7)"},
        std::pair<std::string, std::string> {"xp3 * (- xp1) * (xp1 * A) ^ T * A + D + D", "xp3 * (- xp1) * (xp1 * A) ^ T * A + D + D"},
        std::pair<std::string, std::string> {"a-b-c", "a - b - c"},
        std::pair<std::string, std::string> {"(a-b)-c", "a - b - c"},
        std::pair<std::string, std::string> {"log(exp(12))", "log(exp(12))"}
    };
    
    for(auto it: expresiones_) {
        std::cout << "construct: " << it.first << std::endl;
        Xpres exp = Xpres(it.first);
        std::cout << "needed: " << it.second << std::endl;
        std::cout << "obtained: " << exp << std::endl;
        i++;
    }
    
    /*++++++++++++++++++++++++++++++++*/
    Xpres xp = Xpres("A*(~A)");
    double * arr;
    arr = new double[9]{  1, -2,   7,
                        1.4,  3, -23,
                          4,  1, 0.4};
    Matrix<double> A = Matrix<double>(3, 3, arr);
    arr = new double[9]{  1, -2,   7,
                        1.4,  3, -23,
                          4,  1, 0.4};

    std::cout << "-------------------" << std::endl;
    std::cout << "evaluate xpres 'A * (~A)' with two distinct Matrix: " << std::endl;
    std::cout << "1: " << std::endl;
    xp.set_value("A", A);
    print_this(xp.evaluate());
    
    std::cout << "2: " << std::endl;
    xp.set_value("A", Matrix<double>(3, 3, arr));
    print_this(xp.evaluate());

    /*++++++++++++++++++++++++++++++++*/
    std::cout << "-------------------" << std::endl;
    std::cout << "evaluate xpres 'a - b - c' with a = 1, b = 1, c = 7: " << std::endl;
    Xpres xp1 = "a-b-c"_exp;
    std::cout << xp1.set_value<int64_t>("a", 1) << std::endl;
    std::cout << xp1.set_value<int64_t>("b", 1) << std::endl;
    std::cout << xp1.set_value<int64_t>("c", 7) << std::endl;
    print_this(xp1.evaluate());

    /*++++++++++++++++++++++++++++++++*/
    std::cout << "-------------------" << std::endl;
    std::cout << "make changes in the xpres : " << std::endl;
    Xpres xp2 = "(1.211 - A*.34 + !(Ni))*4 ^ (1.0/7) * A + A"_exp;
    Xpres::iterator it2 = Xpres::iterator(xp2);
    std::cout << xp2 << std::endl;
    it2[0];
    it2.replace_token("A", "B");
    xp2.set_value<int64_t>("A", 2);
    xp2.set_value<int64_t>("Ni", 2);
    xp2.set_value<int64_t>("B", 2);
    std::cout << xp2 << std::endl;
    std::cout << "evaluate xpres with A = 2, Ni = 2, B = 2: " << std::endl;
    print_this(xp2.evaluate());
    
    /*++++++++++++++++++++++++++++++++*/
    std::cout << "-------------------" << std::endl;
    std::cout << "manipulating the xpres : " << std::endl; 
    Xpres xp3 = "(1.211 - A*.34 + !(Ni))*4 ^ (1.0/7) * A + A"_exp;
    std::cout << xp3 << std::endl;
    xp3.set_value<int64_t>("A", 2);
    xp3.set_value<int64_t>("Ni", 2);

    std::cout << "(A) take the first part of the less presendence operator : " << std::endl; 
    Xpres::iterator it3 = Xpres::iterator(xp3);
    it3[0];
    std::cout << it3 << std::endl;
    
    Xpres xp4 = "A - Ni + 4"_exp;
    xp4.set_value<int64_t>("A", 3);
    xp4.set_value<int64_t>("Ni", 3);
    
    std::cout << "(B) exchange token 'A' with xpres 'A - Ni + 4' in (A) where A = 3, Ni = 3 : " << std::endl; 
    it3.replace_token("A", xp4);
    std::cout << xp3 << std::endl;

    std::cout << "(C) take the first part of the less presendence operator of (A) : " << std::endl; 
    it3[0];
    std::cout << it3 << std::endl;
    
    std::cout << "(D) exchange token 'Ni_' with xpres 'B + a' : " << std::endl; 
    it3.replace_token("Ni_", "B + a"_exp);
    std::cout << it3 << std::endl;
    
    std::cout << "(E) take the second part of the less presendence operator of (D) : " << std::endl; 
    it3[1];
    std::cout << it3 << std::endl;

    std::cout << "(F) replace all the expresion (D) for 'r*c' : " << std::endl; 
    it3.replace_current("r * c"_exp); 
    std::cout << xp3 << std::endl;
 
    std::cout << "(G) replace token 'A_' by 'c': " << std::endl; 
    xp3.replace_token("A_", "c");
    std::cout << xp3 << std::endl;

    std::cout << "(H) quit token 'c': " << std::endl; 
    Xpres::iterator(xp3).quit_token("c");
    std::cout << xp3 << std::endl;
    
    std::cout << "(I) replace token 'A_' by 'c': " << std::endl; 
    xp3.replace_token("A", "r + R*q"_exp);
    std::cout << xp3 << std::endl;

    //++++++++++++++++++++++++++++++++
    std::cout << "-------------------" << std::endl;
    std::cout << "proof of potence : A * A" << std::endl;
    Xpres xp5 = "A * A"_exp;
    Xpres::iterator it5 = Xpres::iterator(xp5);
    it5.potence (0, 1);
    std::cout << xp5 << std::endl;
    
    std::cout << "proof of potence : 1 * (R + q) * A * rt * A" << std::endl;
    xp5 = "1 * (R + q) * A * rt * A"_exp;
    it5 = Xpres::iterator(xp5);
    it5.potence (2, 4);
    std::cout << xp5 << std::endl;

    std::cout << "proof of potence : (R + q)^3 * (R + q)^(a+b) * 4" << std::endl;
    xp5 = "(R + q)^3 * (R + q)^(a+b) * 4"_exp;
    it5 = Xpres::iterator(xp5);
    it5.potence (0, 1);
    std::cout << xp5 << std::endl;

    std::cout << "proof of potence : !a^3 * !a * !a^(a+b) * 4" << std::endl;
    xp5 = "(!a)^3 * !a * (!a)^(a+b) * 4"_exp;
    it5 = Xpres::iterator(xp5);
    it5.potence (1, 2);
    std::cout << xp5 << std::endl;
    
    std::cout << "proof of potence : !a * !a^3 * !a^(a+b) * 4" << std::endl;
    xp5 = "!a * !a^3 * (!a)^(a+b) * 4"_exp;
    it5 = Xpres::iterator(xp5);
    it5.potence (0, 1);
    std::cout << xp5 << std::endl;
    
    //++++++++++++++++++++++++++++++++
    std::cout << "-------------------" << std::endl;
    std::cout << "depotence the expression:" << std::endl;
    it5.potence (0, 1);
    std::cout << xp5 << std::endl;
    it5[0].depotence ();
    std::cout << xp5 << std::endl;

    std::cout << "depotence the expression:" << std::endl;
    xp5 = "1 + Q^(a + r + 1) - 4"_exp;
    std::cout << xp5 << std::endl;
    it5 = Xpres::iterator(xp5)[1].depotence();
    std::cout << xp5 << std::endl;

    xp5 = "a + r"_exp;
    Xpres::iterator(xp5)[0].replace_current("!t"_exp);
    std::cout << xp5 << std::endl;
    
    //++++++++++++++++++++++++++++++++
    std::cout << "-------------------" << std::endl;
    std::cout << "prueba de compose: x*r + q*x + 1" << std::endl;
    xp5 = "x*r + q*x + 1"_exp;
    Xpres::iterator (xp5).compose(0, 1, "x");
    std::cout << xp5 << std::endl;
    
    std::cout << "prueba de compose: (x*r*r + q*x*r) * 1" << std::endl;
    xp5 = "(x*r*r + q*x*r) * 1"_exp;
    it5 = Xpres::iterator (xp5)[0].compose(0, 1, "x");
    std::cout << xp5;
    std::cout << it5;
   
    std::cout << "prueba de compose: x*r*r + q*x*r" << std::endl;
    xp5 = "x*r*r + q*x*r"_exp;
    it5 = Xpres::iterator (xp5).compose(0, 1, "x");
    std::cout << xp5;
    std::cout << it5;
    it5[1].compose(0, 1, "r");
    std::cout << xp5 << std::endl;
    
    //++++++++++++++++++++++++++++++++
    std::cout << "-------------------" << std::endl;
    std::cout << "prueba de compose para multiplicacion y division: x*r + x/3" << std::endl;
    xp5 = "x*r + x/3"_exp;
    Xpres::iterator (xp5).compose(0, 1, "x");
    std::cout << xp5 << std::endl;
    
    std::cout << "prueba de compose: t + x*r*r + (r*x)/q + r" << std::endl;
    xp5 = "t + x*r*r + (r*x)/q + r"_exp;
    it5 = Xpres::iterator (xp5).compose(1, 2, "x");
    std::cout << xp5 << std::endl;
    it5[0][1].compose (0, 1, "r");
    std::cout << xp5 << std::endl;

    std::cout << "prueba de compose: t + x + x + r" << std::endl;
    xp5 = "t + x + x + r"_exp;
    it5 = Xpres::iterator (xp5).compose(1, 2, "x");
    std::cout << xp5 << std::endl;

    std::cout << "prueba de compose: t + x + x*3 + r" << std::endl;
    xp5 = "t + x + x*3 + r"_exp;
    it5 = Xpres::iterator (xp5).compose(1, 2, "x");
    std::cout << xp5 << std::endl;

    std::cout << "prueba de compose: t + 3*x*t + x + r" << std::endl;
    xp5 = "t + 3*x*t + x + r"_exp;
    it5 = Xpres::iterator (xp5).compose(1, 2, "x");
    std::cout << xp5 << std::endl;

    std::cout << "prueba de compose:" << std::endl;
    xp5 = "p/(x*t) + p"_exp;
    std::cout << xp5 << std::endl;
    it5 = Xpres::iterator (xp5).compose(0, 1, "p");
    std::cout << xp5 << std::endl;

    std::cout << "prueba de compose:" << std::endl;
    xp5 = "q - r*q"_exp;
    std::cout << xp5 << std::endl;
    it5 = Xpres::iterator (xp5).compose(0, 1, "q");
    std::cout << xp5 << std::endl;

    std::cout << "prueba de compose:" << std::endl;
    xp5 = "q - (q)/t"_exp;
    std::cout << xp5 << std::endl;
    it5 = Xpres::iterator (xp5).compose(0, 1, "q");
    std::cout << xp5 << std::endl;

    std::cout << "prueba de compose:" << std::endl;
    xp5 = "q*r - (q*r*t)"_exp;
    std::cout << xp5 << std::endl;
    it5 = Xpres::iterator (xp5).compose(0, 1, "q");
    std::cout << xp5 << std::endl;
    it5 = Xpres::iterator (xp5)[1].compose(0, 1, "r");
    std::cout << xp5 << std::endl;

    std::cout << "prueba de compose:" << std::endl;
    xp5 = "hola + q/r - q/(q*t)"_exp;
    std::cout << xp5 << std::endl;
    it5 = Xpres::iterator (xp5).compose(1, 2, "q");
    std::cout << xp5 << std::endl;

    std::cout << "prueba de compose:" << std::endl;
    xp5 = "q*r - q/(q*t)"_exp;
    std::cout << xp5 << std::endl;
    it5 = Xpres::iterator (xp5).compose(0, 1, "q");
    std::cout << xp5 << std::endl;

    std::cout << "prueba de compose:" << std::endl;
    xp5 = "q/r + t*5 - 1 + q/(q*t)"_exp;
    std::cout << xp5 << std::endl;
    it5 = Xpres::iterator (xp5).compose(0, 3, "q");
    std::cout << xp5 << std::endl;

    std::cout << "prueba de compose:" << std::endl;
    xp5 = "-q/r + t*5 - 1 - q*q*t"_exp;
    std::cout << xp5 << std::endl;
    it5 = Xpres::iterator (xp5).compose(0, 3, "q");
    std::cout << xp5 << std::endl;

    std::cout << "prueba de compose:" << std::endl;
    xp5 = "-q*r + t*5 - 1 - q*q*t"_exp;
    std::cout << xp5 << std::endl;
    it5 = Xpres::iterator (xp5).compose(0, 3, "q");
    std::cout << xp5 << std::endl;

    std::cout << "prueba de compose:" << std::endl;
    xp5 = "-q/r + t*5 - 1 - q*q/t"_exp;
    std::cout << xp5 << std::endl;
    it5 = Xpres::iterator (xp5).compose(0, 3, "q");
    std::cout << xp5 << std::endl;

    std::cout << "prueba de compose:" << std::endl;
    xp5 = "a - a + a + a - a"_exp;
    std::cout << xp5 << std::endl;
    it5 = Xpres::iterator (xp5).compose(0, 1, "a").compose(0, 1, "a").compose(0, 1, "a").compose(0, 1, "a");
    std::cout << xp5 << std::endl;

    //++++++++++++++++++++++++++++++++
    std::cout << "-------------------" << std::endl;
    std::cout << "prueba igual:" << std::endl;
    xp1 = "a + 4*(r+ t-r/t)"_exp;
    xp2 = "b + 4*(r + t - r/t)"_exp;
    xp3 = "a + 4*(p + e - p/e)"_exp;
    xp4 = "r + 4*(r+t-r/t)"_exp;
    if (xp1 == xp2) {
        std::cout << xp1.to_string() << " == " << xp2.to_string() << std::endl;
    }
    if (xp1 == xp3) {
        std::cout << xp1.to_string() << " == " << xp3.to_string() << std::endl;
    }
    if (xp1 == xp4) {
        std::cout << xp1.to_string() << " == " << xp4.to_string() << std::endl;
    }
    if (xp2 == xp3) {
        std::cout << xp2.to_string() << " == " << xp3.to_string() << std::endl;
    }
    if (xp2 == xp4) {
        std::cout << xp2.to_string() << " == " << xp4.to_string() << std::endl;
    }
    if (xp3 == xp4) {
        std::cout << xp3.to_string() << " == " << xp4.to_string() << std::endl;
    }

    //++++++++++++++++++++++++++++++++
    std::cout << "-------------------" << std::endl;
    std::cout << "proofs of descompose:" << std::endl << std::endl;

    std::cout << "proofs 1:" << std::endl;
    xp5 = "a * (1 + r)"_exp;
    std::cout << xp5 << std::endl;
    it5 = Xpres::iterator (xp5).descompose(1, 0);
    std::cout << xp5 << std::endl;

    std::cout << "proofs 2:" << std::endl;
    xp5 = "1 - (-(1 + r)) * a"_exp;
    std::cout << xp5 << std::endl;
    it5 = Xpres::iterator (xp5)[1][0].descompose(0, 1);
    std::cout << xp5 << std::endl;  

    std::cout << "proofs 3:" << std::endl;
    xp5 = "(a + b) / (3 * !r)"_exp;
    std::cout << xp5 << std::endl;
    it5 = Xpres::iterator (xp5).descompose();
    std::cout << xp5 << std::endl;

    std::cout << "proofs 4:" << std::endl;
    xp5 = "t * y * ((a + b) / !r) * 3"_exp;
    std::cout << xp5 << std::endl;
    it5 = Xpres::iterator (xp5).descompose(2, 1);
    std::cout << xp5 << std::endl;

    std::cout << "proofs 5:" << std::endl;
    xp5 = "((--(a + b)) / !r) * 3"_exp;
    std::cout << xp5 << std::endl;
    it5 = Xpres::iterator (xp5).descompose(0, 1);
    std::cout << xp5 << std::endl;
    
    //++++++++++++++++++++++++++++++++
    std::cout << "-------------------" << std::endl;
    std::cout << "proofs of :" << std::endl << std::endl;
}
