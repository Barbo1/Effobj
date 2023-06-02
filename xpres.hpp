/* This library is meant to define exrepssions. An expression is one with the form, e.i. "A*B-R/!(P%e)".
 * If an expression have terms that can be simplified, it will be(e.i. "A - (B + A) - B" -> "2B"). The 
 * Subexpression can be factorized by a given factor, descopressed or quited. Several operations can be
 * made between expressions and subexpressions.
 */

#include <string>
#include <vector>
#include <cmath>

std::string * _rec_funct_ = {"cos", "acos", "cosh", "sin", "asin", "sinh", "tan", "atan", 
    "tanh", "exp", "log", "log2", "log10"};

typedef _sub_exp_ * sub_expression;

class Expression{
    private:
        _sub_exp_ ;
        Expression();
        Expression(std::string);
        friend Expression operator""_expr(const char8_t*, std::size_t);
    public:
        Expression(const Expression &);
        Expression(Expression &&);
        Expression operator=(const Expression &);
        Expression operator=(Expression &&);

        /*
         *  The operations below are to manipulate the expressions.
         */

        /* Take the identifier of an Subexpression and descompose it. */
        Expression descposition(unsigned);
        /* take the identifier of two Subexpression and factorize the "string parameter" token. */
        Expression factorization(unsigned, unsigned, std::string);
        /* take the identifier of a Subexrepssion and quit it from the Expression. 
         * This can be made too with the operator-().*/
        Expression quit_subexp(unsigned);

        /* Operate the first level of Subexpresions. */

        Expression operator+(const Expression &);
        Expression operator-(const Expression &);
        Expression operator*(const Expression &);
        Expression operator/(const Expression &);
        Expression operator^(const Expression &);
        Expression operator!(const Expression &);
        Expression operator%(const Expression &);

        /* Operate between the levels of any Subexpression. Here, the first parameter is the 
         * identifier of the Subexpression, and the second is expression to operate. */

        Expression add(unsigned, const Expression &);
        Expression sub(unsigned, const Expression &);
        Expression mul(unsigned, const Expression &);
        Expression div(unsigned, const Expression &);
        Expression mod(unsigned, const Expression &);
        Expression fac(unsigned);
        Expression pot(unsigned, const Expression &);
};

Expression operator""_expr(const char8_t*, std::size_t);

