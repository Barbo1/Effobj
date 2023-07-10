#include <cmath>

#include "./xpres.hpp"

// functions recognized by the expressions.
static std::string funct_rec[] = {"cos", "acos", "cosh", "sin", "asin", 
    "sinh", "tan", "atan", "tanh", "exp", "log", "log2", "log10",
    "C", "P", "gcd", "lcm", "tot"};

static char operators[] = {'>', '<', '|', '&', '~', '+', '-', '*', '/', '%', '^', '!'};

// node that form an expression.
struct exp_struct{
    nodeEX son;
    nodeEX sibling;

    unsigned char type; // 't' to token.
                        // 'p' to operator.
                        // 'f' to function.
                        // '\0' to nothing.
    
    unsigned char id;   // type == 't', represents the tokens id.
                        // type == 'p', represents the operators id.
                        // type == 'f', represents the functions id.
                        // type == '\0', represents nothing.
}

/*
   ------------------------------------------------------------------------------
   Here are the auxiliary functions used to implement the Expressions operations.
   ------------------------------------------------------------------------------
*/

/* Delete a node, and the nodes below and along it. */
static void delete_nodes(nodeEX node){
    if(node != nullptr){
        delete_nodes(node->sibling);
        delete_nodes(node->son); 
        delete node;
    }
}

/*
    Make a copy of the intern structure below a node of the Expression and return
    it. If the parameter first == false, the procedure also will copy the structure
    along.
*/
static nodeEX copy_nodes(nodeEX node){
    if(node == nullptr) {
        return nullptr;
    }
    nodeEX node_new = new exp_struct;
    node_new->name = node->name;
    node_new->id = node->id;
    node_new->sibling = copy_nodes(node->sibling);
    node_new->son = copy_nodes(node->son); 
    return node_new;
}

/*
   ---------------------------------------------------------------------
   Here is the implementation of the operations described in worst.hpp.
   ---------------------------------------------------------------------
*/

Expression::Expression() {
    this->root = new exp_struct;
    this->root->type = 0;
    this->root->id = 0;
    this->root->son = this->root->sibling = nullptr;
}

Expression::Expression(std::string sexp) {
    this->root = new exp_struct;
    this->root->type = 0;
    this->root->id = 0;
    this->root->son = this->root->sibling = nullptr;
}

Expression::Expression(const Expression & tr) {
    if(&tr != this) {
        this->root = copy_nodes(tr.root);
        this->token_name = tr.token_name;
        this->token_value = tr.token_value;
        this->token_node = tr.token_node;
        this->term_node = tr.term_node;
    }
}

Expression::Expression(Expression && tr) noexcept {
    if(&tr != this) {
        this->root = tr.root;
        this->token_name = std::move(tr.token_name);
        this->token_value = std::move(tr.token_value);
        this->token_node = std::move(tr.token_node);
        this->term_node = std::move(tr.term_node);
        tr.root = new exp_struct;
        tr.root->type = 0;
        tr.root->name = "";
        tr.root->son = tr.root->sibling = nullptr;
    }
}

Expression & Expression::operator=(const Expression & tr){
    if(&tr != this) {
        delete_nodes(this->root);
        this->root = copy_nodes(tr.root);
        this->token_name = tr.token_name;
        this->token_value = tr.token_value;
        this->token_node = tr.token_node;
        this->term_node = tr.term_node;
    }
    return *this;
}

Expression & Expression::operator=(Expression && tr) noexcept {
    if(&tr != this){
        delete_nodes(this->root);
        this->root = tr.root;
        this->token_name = std::move(tr.token_name);
        this->token_value = std::move(tr.token_value);
        this->token_node = std::move(tr.token_node);
        this->term_node = std::move(tr.term_node);
        tr.root = new exp_struct;
        tr.root->type = 0;
        tr.root->name = "";
        tr.root->son = tr.root->sibling = nullptr;
    }
    return *this;
}

Expression::~Expression(){
    delete_nodes(this->root);
}

std::string simplify(Expression exp) {
    return "";
}

Expression descposition(unsigned id) {
    return Expression();
}

Expression factorization(unsigned id_1, unsigned id_2, std::string token) {
    return Expression();
}

Expression quit_subexp(unsigned, id) {
    return Expression();
}

pair<char, void*> Evaluate() {
    return pair<'a', nullptr>;
}

template<typename T>
bool give_value(std::string name, T value) {
    return true;
}

Expression operator!(const Expression & exp){
    return Expression();
}
Expression operator^(const Expression & exp){
    return Expression();
}

Expression operator%(const Expression & exp){
    return Expression();
}

Expression operator/(const Expression & exp){
    return Expression();
}

Expression operator*(const Expression & exp){
    return Expression();
}

Expression operator-(const Expression & exp){
    return Expression();
}

Expression operator+(const Expression & exp){
    return Expression();
}
                                           
Expression operator~(const Expression & exp){
    return Expression();
}

Expression operator&(const Expression & exp){
    return Expression();
}

Expression operator|(const Expression & exp){
    return Expression();
}

Expression operator<(const Expression & exp){
    return Expression();
}

Expression operator>(const Expression & exp){
    return Expression();
}
                                            
Expression operator()(const Expression & exp){
    return Expression();
}

Expression fac(unsigned id){
    return Expression();
}

Expression pot(unsigned id, const Expression & exp){
    return Expression();
}

Expression mod(unsigned id, const Expression & exp){
    return Expression();
}

Expression div(unsigned id, const Expression & exp){
    return Expression();
}

Expression mul(unsigned id, const Expression & exp){
    return Expression();
}

Expression sub(unsigned id, const Expression & exp){
    return Expression();
}

Expression add(unsigned id, const Expression & exp){
    return Expression();
}

Expression bneg(unsigned id, const Expression & exp){
    return Expression();
}

Expression band(unsigned id, const Expression & exp){
    return Expression();
}

Expression bor(unsigned id, const Expression & exp){
    return Expression();
}

Expression bls(unsigned id, const Expression & exp){
    return Expression();
}

Expression brs(unsigned id, const Expression & exp){
    return Expression();
}

Expression par(unsigned id){
    return Expression();
}

