#include "../xpres.hpp"

/* "log2", "log10" cannot exists bacause is not acepted a token with numbers and letters. */
std::vector<std::string_view> recognized_functions{"cos", "acos", "cosh", 
                                                "sin", "asin", "sinh", 
                                                "tan", "atan", "tanh", 
                                                "gcd", "lcm", "tot",
                                                "exp", "log"};

const std::vector<char> unitary_operators{'~', '!', '-'};
const std::vector<char> binary_operators{'>', '<', '|', '&', '+', '*', '/', '%', '^'};
const std::vector<char> binary_multi_operators{'|', '&', '+', '*'};
const std::vector<char> binary_nomulti_operators{'>', '<', '/', '%', '^'};
const std::vector<char> operators{'|', '&', '~', '>', '<', '+', '-', '@', '*', '/', '%', '^', '!'};

// node that form an expression.
struct exp_struct{
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

#include "./useful_operations.cpp"

#include "./node_manipulation.cpp"

#include "./deduce_operation_binary.cpp"

#include "./print_operations.cpp"

#include "./validate_string_expresion.cpp"

#include "./basic_operations.cpp"

#include "./evaluate_operation_unitary.cpp"

#include "./evaluate_operation_binary.cpp"

#include "./evaluate_function.cpp"

#include "./evaluate_aux.cpp"

std::pair<char, void*> Xpres::evaluate() const {
    return evaluate_aux(this->root, this->token_info);
}

#include "./operators.cpp"

Xpres operator""_exp(const char* exp, size_t) {
    return Xpres(std::string(exp));
}

std::pair<char, void*> Xpres::iterator::evaluate() const{
    return evaluate_aux(points.top(), token_info);
}

#include "./modification_operations_iterator.cpp"
