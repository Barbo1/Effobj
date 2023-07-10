/* This library is meant to define mathematic exrepssions. The Subexpressions can be simplified,
 * factorized by a given factor, descopressed, quited or you can operate with two expressions using 
 * several operands. The operands can be aplied in any level of the expression.
 * The implementation supports only 256 different tokens.
 */

#ifndef __MOD_EXPRESSION_
#define __MOD_EXPRESSION_

#include <string>
#include <vector>
#include <map>
#include <utility>

#include "./matrix.hpp"

typedef exp_struct * nodeEX;

class Expression{
    private:
        nodeEX root;

        // keeps information of the tokens.
        std::vector<std::string> token_name;
        std::vector<std::pair<char, void*>> token_value;         
        std::vector<nodeEX> token_node;

        // keeps references to the different terms.
        std::vector<nodeEX> term_node; 

        friend Expression operator""_ex(const char8_t*, std::size_t);
    public:
        Expression();
        Expression(std::string sexp, bool simplified); 
        Expression(const Expression & exp);
        Expression(Expression && exp);
        Expression operator=(const Expression & exp);
        Expression operator=(Expression && exp);

        /*
         *  The operations below are to manipulate the expressions.
         */

        /* Take the identifier of an token and descompose it. */
        void descposition(unsigned id);

        /* Take the identifier of two tokens and factorizes the token. */
        void factorization(unsigned id_1, unsigned id_2, std::string token);
        
        /* Take the identifier of a token and quit it from the Expression. 
         * This can be made too with the operator-().*/
        void quit_token(unsigned id);

        /* Take the identifier of a token and replace it with a new expression. */
        void replace_token(unsigned id, Expression exp);

        /* Make all the operations to evalute the expression and return a pair
         * with the type of the value by first parameter and a void pointer to
         * the final value by secon parameter. The posible values to the first
         * parameter are:
         *  - 'M' to matrix<float>.
         *  - 'm' to matrix<int>.
         *  - 'd' to double.
         *  - 'i' to int.
         *  */
        pair<char, void*> Evaluate();

        /* Give a value to the token with the name equal to 'name'. */
        template<typename T>
        bool give_value(std::string name, T value);

        /* 
         * Operate the first level of Subexpresions. 
         */
        
        Expression operator!(const Expression & exp);
        Expression operator^(const Expression & exp);
        Expression operator%(const Expression & exp);
        Expression operator/(const Expression & exp);
        Expression operator*(const Expression & exp);
        Expression operator-(const Expression & exp);
        Expression operator+(const Expression & exp);
        
        Expression operator~(const Expression & exp);
        Expression operator&(const Expression & exp);
        Expression operator|(const Expression & exp);
        Expression operator<(const Expression & exp);
        Expression operator>(const Expression & exp);

        Expression operator()();
       
        /* Operate between the levels of any Subexpression. Here, the first parameter is the 
         * identifier of the Subexpression, and the second is expression to operate. */

        Expression fac(unsigned id);
        Expression pot(unsigned id, const Expression & exp);
        Expression mod(unsigned id, const Expression & exp);
        Expression div(unsigned id, const Expression & exp);
        Expression mul(unsigned id, const Expression & exp);
        Expression sub(unsigned id, const Expression & exp);
        Expression add(unsigned id, const Expression & exp);

        Expression bneg(unsigned id, const Expression & exp);
        Expression band(unsigned id, const Expression & exp);
        Expression bor(unsigned id, const Expression & exp);
        Expression bls(unsigned id, const Expression & exp);
        Expression brs(unsigned id, const Expression & exp);

        Expression par(unsigned id);
};

Expression operator""_ex(const char8_t*, std::size_t);


#endif
