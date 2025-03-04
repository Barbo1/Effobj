#pragma once

#include "./needed.hpp"
#include <vector>
#include <string>
#include <span>
#include <ranges>
#include <cmath>
#include <utility>

class Polynomial {
  private:
    std::size_t size;
    std::vector<iv_x8> grades;
    std::vector<fv_x8> coefficients;

    Polynomial (std::vector<fv_x8>, std::vector<iv_x8>, std::size_t);

  public:
    Polynomial ();
    Polynomial (int);
    Polynomial (float, uint64_t);
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

    float operator[] (unsigned grade);
    unsigned monomial_quan ();

    template <arithmetric X, arithmetric R>
    R operator() (X);

    Polynomial derivate ();
    Polynomial integrate ();

    /* operations only for simple arithmetric types. */
    std::vector<double> get_roots ();
    double aproximate_root ();

    /* friend. */
    friend std::ostream& operator<<(const std::ostream & out, const Polynomial & pol); 
};

std::ostream& operator<<(const std::ostream & out, const Polynomial & pol);
