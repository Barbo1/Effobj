#ifndef __Poly_mod
#define __Poly_mod

#include "./needed.hpp"
#include <vector>
#include <utility>
#include <string_view>
#include <string>
#include <iostream>

template<arithmetric T>
class Polynomial {
    private: 
        std::vector<std::pair<T, index>> _data_;
    public:
        Polynomial ();
        Polynomial (int);
        Polynomial (std::string_view);
        Polynomial (std::vector<std::pair<T, index>>);
        Polynomial (const Polynomial &); // no se si quiero hacer eso.
        Polynomial (Polynomial &&);
        Polynomial& operator= (const Polynomial &);
        Polynomial& operator= (Polynomial &&);
        bool operator== (const Polynomial &);
        ~Polynomial ();
        std::string to_string ();

        Polynomial operator+ (const Polynomial &);
        Polynomial operator- (const Polynomial &);
        Polynomial operator* (const Polynomial &);
        Polynomial operator/ (const Polynomial &);
        Polynomial operator+= (const Polynomial &);
        Polynomial operator-= (const Polynomial &);
        Polynomial operator*= (const Polynomial &);
        Polynomial operator/= (const Polynomial &);

        std::pair<T, index> operator[] (unsigned);
        unsigned monomial_quan ();
        T evaluate (T);

        Polynomial derivate ();
        Polynomial integrate ();
        
        /* operations only for simple arithmetric types. */
        std::vector<double> get_roots ();
        double aproximate_root ();

        /* friend. */
        friend std::ostream& operator<<(const std::ostream & out, const Polynomial & pol); 
};

template <arithmetric T>
std::ostream& operator<<(const std::ostream & out, const Polynomial<T> & pol);

#endif
