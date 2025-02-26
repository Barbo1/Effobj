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

#pragma once

#include "matrix.hpp" 

#include <array>
#include <tuple>
#include <string>
#include <vector>
#include <utility>
#include <stack>
#include <string_view>
#include <cstdint>
#include <cmath>

// node that form an expression.
using node_t = int8_t;
using data_t = int64_t;

typedef struct exp_struct * nodeEX;
struct exp_struct {
  nodeEX son;
  nodeEX sibling;

  node_t type;        // 't' to token.
                      // 'd' to double.
                      // 'i' to integer.
                      // 'p' to operator.
                      // 'f' to function.
                      // '\0' to nothing.

  data_t id;          // type == 't', represents the tokens id.
                      // type == 'd', represents a double (needs cast).
                      // type == 'i', represents a integer.
                      // type == 'p', represents the operators id.
                      // type == 'f', represents the functions id.
                      // type == '\0', represents nothing.
};

class Xpres {
  private:
    /********************
     *    Data to use   *
     ********************/

    /* "log2", "log10" cannot exists bacause is not acepted a token with 
     * numbers and letters. 
     * */
    static constexpr std::array<std::string_view, 14> recognized_functions {
      "cos", "acos", "cosh", "sin", "asin", "sinh", "tan", 
        "atan", "tanh", "gcd", "lcm", "tot", "exp", "log"
    };
    static constexpr std::array<char, 3> unitary_operators {
      '~', '!', '-'
    };
    static constexpr std::array<char, 9> binary_operators {
      '>', '<', '|', '&', '+', '*', '/', '%', '^'
    };
    static constexpr std::array<char, 4> binary_multi_operators {
      '|', '&', '+', '*'
    };
    static constexpr std::array<char, 5> binary_nomulti_operators {
      '>', '<', '/', '%', '^'
    };
    static constexpr std::array<char, 13> operators {
      '|', '&', '~', '>', '<', '+', '-', '@', '*', '/', '%', '^', '!'
    };


    /***************************
     *    useful operations    *
     ***************************/

    std::string get_new_name(std::string str);

    static void exchange_pair (std::pair<char, void*> op1, std::pair<char, void*> op2);
    static void free_pair(std::pair<char, void*>);
    static std::pair<char, void*> copy_pair(std::pair<char, void*>);

    template<typename T>
    static int exists(T var, const std::vector<T> & arr);

    template<typename T, std::size_t N>
    static int exists(T var, const std::array<T, N> & arr);

    template<typename T>
    static void quit_from(T var, const std::vector<T> & arr);

    static bool is_oper_bm (uint8_t op);
    static bool is_oper_b (uint8_t op);
    static bool is_oper_u (uint8_t op);

    static bool is_character(char let);
    static bool is_digit(char let);

    /*  precondition: op1 and op2 are operators. Returns 0 if both are the same
     *  operator, 1 of first operator have more precedence, and -1 in other case.
     * */
    static int precedence (char, char);


    /***************************
     *    note manipulation    *
     ***************************/

    static nodeEX create_node (
      uint8_t type, 
      uint64_t id, 
      nodeEX son = nullptr, 
      nodeEX sibling = nullptr
    ) noexcept;

    static void delete_nodes(nodeEX node) noexcept;

    static nodeEX copy_nodes (nodeEX node, bool not_same_level = true) noexcept;

    /* Add n to the id of each token node. */
    static void add_ids (nodeEX root, uint64_t n) noexcept;

    /* Recalculate the token node's id depending on the array passed by parameter. */
    static nodeEX recalculate_ids (nodeEX node, uint64_t * arr) noexcept;

    /* Change the id of the tokens with id == idold to be idnew, in the 
     * node below last_son (included). 
     * */
    static void change_id (const uint64_t idold, const uint64_t idnew, nodeEX last_son) noexcept;

    /* Change the ocurrences of token nodes with id == idold with a copy of 
     * node_exp tree, below last_son. Probably this function need to be 
     * used after using recalculte_ids.
     * */
    static bool change_tree(const uint64_t idold, nodeEX node_exp, nodeEX last_son) noexcept;

    /* This function returns a two dimentional array of 2 by length that contains:
     * - true in the first row in the positions which index represent a node 
     *    outer the last_son subtree, false otherwise.
     * - true in the second row in the positions which index represent a node 
     *    inner the last_son subtree, false otherwise.
     * */
    static void repetition_counter_arr_aux(
      nodeEX root, 
      const nodeEX last_son, 
      uint64_t index, 
      const uint64_t & length, 
      bool * arr
    ) noexcept;
    static bool * repetition_counter_arr(nodeEX root, const nodeEX last_son, uint64_t length) noexcept;

    /* Returns an array that contains true in the positions which index represent 
     * the id of the token nodes outer the last_son subtree, false otherwise.
     * */
    static void repetition_counter_outer_arr_aux(nodeEX root, const nodeEX last_son, bool * arr) noexcept;
    static bool * repetition_counter_outer_arr(
      nodeEX root, 
      const nodeEX last_son, 
      uint64_t length
    ) noexcept;

    /* Returns true if outer token nodes has id == idold. */
    static bool repetition_counter_outer(nodeEX root, const nodeEX last_son, uint64_t idold) noexcept;

    /* Get a nodeEX and put it in the begining of the "sons array". 
     * The sontc need to be a son of father. 
     * */
    static void put_first (const nodeEX father, nodeEX sontc) noexcept;

    /* Get an array with the nodes that are sons of the 'father' node in order. */
    static std::vector<nodeEX> get_array_sons (nodeEX father) noexcept;

    /* Compare two trees to see if they represent the same expresion. That means that 
     * the names and values of two token can be different but the expresion remains the 
     * same (i.e. "a + b*c"_exp = "r + q*r"_exp).
     * Precondition: both trees have the same quantitys of tokens (max_id).
     * */
    static bool compare_tree_similar_aux (
      nodeEX root1, 
      nodeEX root2, 
      uint64_t * arr, 
      bool not_same_level = false
    ) noexcept;
    static bool compare_tree_similar (nodeEX root1, nodeEX root2, uint64_t max_id) noexcept;

    /* Compare two trees to see if they are exactly the same. */
    static bool compare_tree_equal (nodeEX root1, nodeEX root2, bool not_same_level = false) noexcept;

    std::vector< std::tuple< std::string, char, void*> > get_tokens ();


    /*****************
     *    helpers    *
     *****************/

    Xpres& operate_operator (const char oper, Xpres& xp, const Xpres& exp);

    /* This function is meant to make the evaluation of two operands with the 
     * passed operator 'ope'. It will work only for unary operators (the next 
     * function is for binary).
     * */
    static std::pair<char, void*> evaluate_operator_unitary (
      std::pair<char, void*> op1, 
      const char ope
    );

    /* This function is meant to make the evaluation of two operands with the 
     * passed operator 'ope'. It will work only for unary operators (the next 
     * function is for binary).
     * */
    static std::pair<char, void*> evaluate_operator_binary (
      std::pair<char, void*> op1, 
      std::pair<char, void*> op2, 
      const char ope
    );

    /* This operation is used to create nodes and/or put them in proper order.
     * precondition 1: op belongs to operators.
     * clarification: op is the operator from the stack of operators, and the 
     * others are from the stack of operands.
     * */
    static nodeEX deduce_operation_binary (nodeEX res_1, nodeEX res_2, const char op);

    static std::pair<char, void*> evaluate_aux (
      nodeEX node,
      const std::vector<std::tuple<std::string, char, void*>> & token_info
    );

    static std::pair<char, void*> evaluate_function (std::pair<char, void*> op1, std::string_view fun);

    static std::string to_string_aux (
      nodeEX father, 
      nodeEX first_son, 
      const std::vector<std::tuple<std::string, char, void*>> & token_info, 
      bool no_first = false
    ) noexcept;

    /* this function is used to transform the expresions in string. */ 
    static std::string to_string_node (
      nodeEX root, 
      const std::vector<std::tuple<std::string, char, void*>> & token_info
    ) noexcept;


    /**************************
     *    token operations    *
     **************************/

    static nodeEX get_root (std::stack<nodeEX> st_this);

    static bool quit_token_aux(nodeEX root, const uint64_t idname, bool recalculate_ids);


    /**************
     *    Data    *
     **************/

    nodeEX root;

    /* keeps information of the tokens where the string is the name of 
     * the token, the char is the type of value the token has and the 
     * void* is a pointer ot his value.
     * */
    std::vector< std::tuple< std::string, char, void*> > token_info; 

  public:
    Xpres(); 

    /* This is the constructor that make an expresion form a string.
     * Precondition: the string is a valid expresion, that menas,
     * validate_string_expresion(sexp) == true. 
     * */
    Xpres(std::string_view sexp);

    Xpres(const Xpres & exp); 
    Xpres(Xpres && exp) noexcept; 
    Xpres& operator=(const Xpres & exp) noexcept; 
    Xpres& operator=(Xpres && exp) noexcept; 
    bool operator==(const Xpres & exp) const noexcept; 
    ~Xpres();

    /* Convertion methods. */
    Xpres(int i);
    Xpres(double d);
    std::string to_string() const noexcept; 

    /* Take the name of a token and quit the appearances. This means 
     * that if the token is adding, then will be changed by 0, y is 
     * multiplying, then will be changed by 1, etc.
     * */
    Xpres& quit_token(std::string_view name);

    /* Take the name nold of the old token and replace the appearances
     * in the current "scope" with a expresion. 
     * */
    Xpres& replace_token(std::string_view nold, const Xpres & exp);

    /* Take the name nold of the old token and replace the appearances 
     * with the nnew token. 
     * */
    Xpres& replace_token(std::string_view nold, std::string_view nnew);

    /* If the operation needs no expression, it will be applied in all 
     * the expresion. If the operation takes an expression, then 
     * concatenate both with the operator considered.
     * */

    Xpres operator!();
    Xpres operator-();
    Xpres operator~();
    Xpres apply_function(std::string_view func_name);

    Xpres operator-=(const Xpres & exp);
    Xpres operator/=(const Xpres & exp);
    Xpres operator*=(const Xpres & exp);
    Xpres operator+=(const Xpres & exp);

    Xpres operator-(const Xpres & exp);
    Xpres operator^(const Xpres & exp);
    Xpres operator%(const Xpres & exp);
    Xpres operator/(const Xpres & exp);
    Xpres operator*(const Xpres & exp);
    Xpres operator+(const Xpres & exp);
    Xpres operator<(const Xpres & exp);
    Xpres operator>(const Xpres & exp);
    Xpres operator&(const Xpres & exp);
    Xpres operator|(const Xpres & exp);

    /* Make all the operations to evalute the expression and return a pair
     * with the type of the value by first parameter and a void pointer to
     * the final value by second parameter. The posible values to the first
     * parameter are:
     * - 'E' to matrix<Xpres>.
     * - 'M' to matrix<double>.
     * - 'm' to matrix<int64_t>.
     * - 'e' to Xpres.
     * - 'd' to double.
     * - 'i' to int64_t.
     * */
    std::pair<char, void*> evaluate() const;

    /* Give a value to the token with the name equal to 'name'. If there is no 
     * token with such name, nothing will change and false will return. 
     * */
    template <typename T>
      bool set_value(std::string_view name, const T& value);

    /* Take the value of the token with the name equal to 'name'. If there is 
     * no token with such name, return a {0, null} pair. 
     * */
    std::pair<char, void*> get_value(std::string_view name);

    /* validate if a string is a valid expresion. */
    bool validate_string_expresion(std::string_view sexp_view);

    /* The iterator class is meant to control the operations of the expression. 
     * With it, you can change all parts of the expression that you want.
     * */
    class iterator{
      private:
        void almost_empty_points(std::stack<nodeEX>& points);
        void operate_operator_iterator(const char oper, Xpres::iterator& it, const Xpres& exp);

        /**************
         *    Data    *
         **************/
        
        Xpres & expresion;
        std::stack<nodeEX> points;
        std::vector< std::tuple< std::string, char, void*> > & token_info;

      public:
        /* No default constructor. */
        iterator(Xpres & exp);
        iterator(const iterator & it);
        iterator(iterator && it);
        iterator& operator=(const iterator & it);
        iterator& operator=(iterator && it);

        /* Take the identifiers of two subexpresions and compose them, this means:
         * brings the subexpression a*b + a*c and put the subexpression a*(b+c). 
         * */
        iterator& compose(uint64_t id_1, uint64_t id_2, std::string_view name);

        /* Make the inverse operation of above. */
        iterator& descompose(uint64_t id_1, uint64_t id_2);

        /* Take the identifiers of two subexpresions and potence them, this
         * means: if the subexpressions are realted by * and have the tokens,
         * like a*b*...*c*a^2*d where the subexpressions are a and a^2, then 
         * the expression change to be a^3*b*...*c*d. 
         * */
        iterator& potence(uint64_t id_1, uint64_t id_2);

        /* Take the identifier of an subexpresion and degrade it, this means:
         * if an expression exp and a number p realted by ^, then exp*exp*...*exp
         * p times will be puted in the expression.
         * */
        iterator& depotence();

        /* Take the name of a token and quit the appearances in the current 
         * "scope". This means that if the token is adding, then will be 
         * changed by 0, y is multiplying, then will be changed by 1, etc.
         * */
        iterator& quit_token(std::string_view name);

        /* Replace the current "scope" with a expresion. */
        iterator& replace_current(const Xpres & exp);

        /* Take the name nold of the old token and replace the appearances in 
         * the current "scope" with a expresion. 
         * */
        iterator& replace_token(std::string_view nold, const Xpres & exp);

        /* Take the name nold of the old token and replace the appearances in 
         * the current "scope" with the nnew token. 
         * */
        iterator& replace_token(std::string_view nold, std::string_view nnew);

        /* Make all the operations to evalute the expression and return a pair
         * with the type of the value by first parameter and a void pointer to
         * the final value by secon parameter. The posible values to the first
         * parameter are:
         * - 'E' to matrix<Xpres>.
         * - 'M' to matrix<double>.
         * - 'm' to matrix<int64_t>.
         * - 'e' to Xpres.
         * - 'd' to double.
         * - 'i' to int64_t.
         * */
        std::pair<char, void*> evaluate() const;

        /* This is the operator to access the son's operands, be these the operators
         * or operands. If an non existent son index is passed, no operation were 
         * be made, and zero will be returned.
         * */
        iterator& operator[](int64_t index); 

        /* All the below operations are made in the current scope of the iterator.
         * If the operation needs no expression, the operation will be applied 
         * in the curret scope. If the operation take an expression, then 
         * concatenate that expresion with the subexpression in the current
         * scope using the operator.
         * */

        iterator& operator!(); 
        iterator& operator-(); 
        iterator& operator~(); 
        iterator& apply_function(std::string_view func_name); 

        iterator& operator-(const Xpres & exp); 
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
        friend std::ostream& operator<< (std::ostream & of, const iterator & it);
        friend void operate_operator_iterator (
          const char oper, 
          iterator& it, 
          const Xpres& exp
        ); 
    };

    /* friendship. */
    friend Xpres operator""_exp (const char*, std::size_t);
    friend void operate_operator_iterator (
      const char oper, 
      iterator& it, 
      const Xpres& exp
    ); 
    friend std::ostream& operator<<(std::ostream & of, const Xpres & exp);
    friend std::ostream& operator<<(std::ostream & ofile, const Xpres::iterator & it);

    /* function to make the operator methods. */
    friend Xpres& operate_operator(const char oper, Xpres& obj, const Xpres& exp);
};

Xpres operator""_exp(const char * exp, size_t);

/* Prints the expression. */
std::ostream& operator<<(std::ostream & ofile, const Xpres & exp);
std::ostream& operator<<(std::ostream & ofile, const Xpres::iterator & it);
