#pragma once

#include "./needed.hpp"
#include <vector>
#include <string_view>
#include <string>
#include <iostream>

template <arithmetric T>
class Polynomial {
  private: 
    std::vector<T> coefficients;
    std::vector<T> grades;

  public:
    Polynomial ();
    Polynomial (int);
    Polynomial (T, uint64_t);
    Polynomial (std::string_view);
    Polynomial (const Polynomial &);
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

    T operator[] (unsigned);
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

template <>
class Polynomial<float> {
  private: 
    fv_x4 * coefficients;
    uint64_t * grades;
  public:
    Polynomial ();
    Polynomial (int);
    Polynomial (float, uint64_t);
    Polynomial (std::string_view);
    Polynomial (const Polynomial &);
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

    float operator[] (unsigned);
    unsigned monomial_quan ();
    float evaluate (float);

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
