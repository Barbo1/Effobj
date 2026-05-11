#pragma once

#include "./needed.hpp"
#include "./matrix.hpp"
#include <vector>
#include <string>
#include <cmath>

enum polytype {
  UNIFORM,
  DISCRETE
};

class Polynomial {
  private:
    std::size_t size;
    std::vector<iv_x8> grades;
    std::vector<fv_x8> coefficients;

    Polynomial (std::vector<fv_x8>&, std::vector<iv_x8>&, std::size_t);

  public:
    Polynomial ();                  // create 0.
    Polynomial (int);               // create constant.
    Polynomial (float, uint32_t);   // create monomial.
    Polynomial (float*, uint32_t);  // create polynomial.
    Polynomial (const Polynomial &);
    Polynomial (Polynomial &&);
    Polynomial& operator= (const Polynomial &);
    Polynomial& operator= (Polynomial &&);
    bool operator== (const Polynomial &);
    ~Polynomial ();

    std::string to_string ();

    Polynomial operator- ();
    Polynomial operator+ (const Polynomial &);
    Polynomial operator* (const Polynomial &);
    Polynomial operator/ (const Polynomial &);
    Polynomial operator+= (const Polynomial &);
    Polynomial operator*= (const Polynomial &);
    Polynomial operator/= (const Polynomial &);

    float operator[] (unsigned grade);
    std::size_t many_monomials ();

    float operator() (const float& obj);
    Matrix<float> operator() (const Matrix<float>& obj);

    Polynomial derivate ();
    Polynomial integrate ();

    /* operations only for simple arithmetric types. */
    std::vector<double> get_roots ();
    double aproximate_root ();

    /* friend. */
    friend std::ostream& operator<<(const std::ostream & out, const Polynomial & pol); 
    template <semi_arithmetric X>
      friend X evaluate_polynomial(
        const Polynomial pol, const X& obj, 
        const X& one, const X& zero
      );
};

std::ostream& operator<<(const std::ostream & out, const Polynomial & pol);
