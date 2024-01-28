/* This library is meant to define mathematic exrepssions. The Subexpressions can be simplified,
 * factorized by a given factor, descopressed, quited or you can operate with two expressions using 
 * several operands. The operands can be aplied in any level of the expression.
 *
 * Some thighs that i want to make in a future:
 *      - operation that do the following: if two expressions exp1*exp2*exp3 and p realted by ^, then 
 *          change (exp1*exp2*exp3)^p by exp1^p * (exp2*exp3)^p.
 *      - I can make a copy of an iterator that copy the pointed subexression to be another expresion.
 *      - an option to create an simplified expression.
 */

#ifndef __MOD_EXPRESSION_
#define __MOD_EXPRESSION_

#include <tuple>
#include <string>
#include <vector>
#include <utility>
#include <stack>
#include <string_view>
#include <inttypes.h>

#include "./matrix.hpp"

typedef struct exp_struct * nodeEX;
typedef int8_t node_t;
typedef int64_t data_t;

class Xpres{
    private:
        nodeEX root;

        // keeps information of the tokens where the string is the name of the token, the
        // char is the type of value the token has and the void* is a pointer ot his value.
        std::vector< std::tuple< std::string, char, void*> > token_info; 
    public:
        Xpres(); 
        Xpres(std::string_view sexp); 
        Xpres(const Xpres & exp); 
        Xpres(Xpres && exp) noexcept; 
        Xpres& operator=(const Xpres & exp); 
        Xpres& operator=(Xpres && exp) noexcept; 
        bool operator==(const Xpres & exp) const noexcept; 
        std::string to_string() const noexcept; 
        ~Xpres();
        
        /* 
            Take the name of a token and quit the appearances. This means 
            that if the token is adding, then will be changed by 0, y is 
            multiplying, then will be changed by 1, etc.
         */
        Xpres& quit_token(std::string_view name);

        /* 
            Take the name nold of the old token and replace the appearances
            in the current "scope" with a expresion. 
         */
        Xpres& replace_token(std::string_view nold, const Xpres & exp);
 
        /* 
            Take the name nold of the old token and replace the appearances 
            with the nnew token. 
         */
        Xpres& replace_token(std::string_view nold, std::string_view nnew);

        /* 
            If the operation needs no expression, it will be applied in all 
            the expresion. If the operation takes an expression, then 
            concatenate both with the operator considered.
        */

        Xpres operator!();
        Xpres operator-();
        Xpres operator~();
        Xpres apply_function(std::string_view func_name);

        Xpres operator^(const Xpres & exp);
        Xpres operator%(const Xpres & exp);
        Xpres operator/(const Xpres & exp);
        Xpres operator*(const Xpres & exp);
        Xpres operator+(const Xpres & exp);
        Xpres operator<(const Xpres & exp);
        Xpres operator>(const Xpres & exp);
        Xpres operator&(const Xpres & exp);
        Xpres operator|(const Xpres & exp);

        /* 
            Make all the operations to evalute the expression and return a pair
            with the type of the value by first parameter and a void pointer to
            the final value by second parameter. The posible values to the first
            parameter are:
                - 'E' to matrix<Xpres>.
                - 'M' to matrix<double>.
                - 'm' to matrix<int64_t>.
                - 'e' to Xpres.
                - 'd' to double.
                - 'i' to int64_t.
        */
        std::pair<char, void*> evaluate() const;

        #include "./xpres_files/set_get_value.hpp"

        /* 
            The iterator class is meant to control the operations of the expression. With it, you
            can change all parts of the expression that you want.
        */
        class iterator{
            private:
                std::stack<nodeEX> points;
                std::vector< std::tuple< std::string, char, void*> > & token_info;
            public: 
                /* No default constructor. */
                iterator(Xpres & exp);
                iterator(const iterator & it);
                iterator(iterator && it);
                iterator& operator=(const iterator & it);
                iterator& operator=(iterator && it);
                
                /* 
                    Take the identifiers of two subexpresions and compose them, this means:
                    brings the subexpression a*b + a*c and put the subexpression a*(b+c). 
                */
                iterator& compose(uint64_t id_1, uint64_t id_2, std::string_view name);

                /* 
                    Make the inverse operation of above.
                */
                iterator& descompose(uint64_t id_1, uint64_t id_2);

                /* 
                    Take the identifiers of two subexpresions and potence them, this
                    means: if the subexpressions are realted by * and have the tokens,
                    like a*b*...*c*a^2*d where the subexpressions are a and a^2, then 
                    the expression change to be a^3*b*...*c*d. 
                */
                iterator& potence(uint64_t id_1, uint64_t id_2);

                /* 
                    Take the identifier of an subexpresion and degrade it, this means:
                    if an expression exp and a number p realted by ^, then exp*exp*...*exp
                    p times will be puted in the expression.
                */
                iterator& depotence();

                /* 
                    Take the name of a token and quit the appearances in the current 
                    "scope". This means that if the token is adding, then will be 
                    changed by 0, y is multiplying, then will be changed by 1, etc.
                */
                iterator& quit_token(std::string_view name);
                
                /* Replace the current "scope" with a expresion. */
                iterator& replace_current(const Xpres & exp);

                /* 
                    Take the name nold of the old token and replace the appearances in 
                    the current "scope" with a expresion. 
                */
                iterator& replace_token(std::string_view nold, const Xpres & exp);

                /* 
                    Take the name nold of the old token and replace the appearances in 
                    the current "scope" with the nnew token. 
                */
                iterator& replace_token(std::string_view nold, std::string_view nnew);

                /* 
                    Make all the operations to evalute the expression and return a pair
                    with the type of the value by first parameter and a void pointer to
                    the final value by secon parameter. The posible values to the first
                    parameter are:
                        - 'M' to matrix<float>.
                        - 'm' to matrix<int>.
                        - 'd' to double.
                        - 'i' to long int.
                        - 'e' to expresion.
                */
                std::pair<char, void*> evaluate() const;

                /* 
                    This is the operator to access the son's operands, be these the operators
                    or operands. If an non existent son index is passed, no operation were 
                    be made, and zero will be returned.
                */

                iterator& operator[](int64_t index); 

                /* 
                    All the below operations are made in the current scope of the iterator.
                    If the operation needs no expression, the operation will be applied 
                    in the curret scope. If the operation take an expression, then 
                    concatenate that expresion with the subexpression in the current
                    scope using the operator.
                */

                iterator& operator!(); 
                iterator& operator-(); 
                iterator& operator~(); 
                iterator& apply_function(std::string_view func_name); 

                iterator& operator^(const Xpres & exp); 
                iterator& operator%(const Xpres & exp); 
                iterator& operator/(const Xpres & exp); 
                iterator& operator*(const Xpres & exp); 
                iterator& operator+(const Xpres & exp); 
                iterator& operator<(const Xpres & exp); 
                iterator& operator>(const Xpres & exp); 
                iterator& operator&(const Xpres & exp); 
                iterator& operator|(const Xpres & exp); 
                
                /* friendship. */
                friend std::ostream& operator<<(std::ostream & of, const iterator & it);
        };

        /* friendship. */
        friend Xpres operator""_exp(const char8_t*, std::size_t);
        friend std::ostream& operator<<(std::ostream & of, const Xpres & exp);
};

Xpres operator""_exp(const char * exp, size_t);

/* Prints the expression. */
std::ostream& operator<<(std::ostream & ofile, const Xpres & exp);

std::ostream& operator<<(std::ostream & ofile, const Xpres::iterator & it);

/* validate if a string is a valid expresion. */
bool validate_string_expresion(std::string_view sexp_view);

#include "./xpres_files/xpres.cpp"

#endif
