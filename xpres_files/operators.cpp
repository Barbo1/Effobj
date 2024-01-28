
/* I need to change this. This functions will be inline, and probably some will be the same of his iterator .*/

#define token_info_f() \
    xp.token_info = token_info; \
    std::vector<uint64_t> vecc; \
    const uint64_t n = token_info.size(); \
    uint64_t cont = n; \
    uint64_t i; \
    for (uint64_t j = 0; j < exp.token_info.size(); j++) { \
        i = 0; \
        while (i < n && std::get<0>(xp.token_info[i]) != std::get<0>(exp.token_info[j])) { \
            i++; \
        } \
        if (i == n) { \
            xp.token_info.push_back(exp.token_info[j]); \
            vecc.push_back(cont++); \
        } else { \
            vecc.push_back(i); \
        } \
    } \
    recalculate_ids(prin, &vecc[0]); \

#define operate_multi_operator(oper) \
    Xpres xp = Xpres(*this); \
    nodeEX prin; \
    if (this->root->type == 'p' && this->root->id == oper) { \
        prin = xp.root->son; \
    } else { \
        prin = xp.root; \
        xp.root = create_node('p', oper, prin); \
    } \
    while (prin->sibling != nullptr) { \
        prin = prin->sibling; \
    } \
    if (exp.root->type == 'p' && exp.root->id == oper) { \
        prin = (prin->sibling = copy_nodes(exp.root->son, false)); \
    } else { \
        prin = (prin->sibling = copy_nodes(exp.root, false)); \
    } \

#define operate_only_operator(oper) \
    Xpres xp = Xpres(*this); \
    xp.root = create_node('p', oper, xp.root); \
    nodeEX prin = (xp.root->son->sibling = copy_nodes(exp.root, false)); \

/*-------------------------------------iterator-----------------------------------------*/

#define almost_empty_points() \
    while (points.size() != 1) { \
        points.pop(); \
    } \

#define operate_multi_operator_iterator(oper) \
    nodeEX prin; \
    nodeEX & res = this->points.top(); \
    if (res->type == 'p' && res->id == oper) { \
        prin = res->son; \
    } else { \
        prin = res; \
        res = create_node('p', oper, prin); \
    } \
    while (prin->sibling != nullptr) { \
        prin = prin->sibling; \
    } \
    if (exp.root->type == 'p' && exp.root->id == oper) { \
        prin->sibling = copy_nodes(exp.root->son, false); \
    } else { \
        prin->sibling = copy_nodes(exp.root, false); \
    } \


#define operate_only_operator_iterator(oper) \
    nodeEX prin = this->points.top(); \
    this->points.top() =  create_node('p', oper, this->points.top()); \
    prin->sibling = copy_nodes(exp.root, false); \


/*--------------------------------------implementation----------------------------------------*/

Xpres Xpres::operator!(){
    Xpres xp = Xpres(*this);
    xp.root = create_node('p', '!', xp.root);
    return xp;
}

Xpres Xpres::operator-(){
    Xpres xp = Xpres(*this);
    xp.root = create_node('p', '-', xp.root);
    return xp;
}

Xpres Xpres::operator~(){
    Xpres xp = Xpres(*this);
    xp.root = create_node('p', '~', xp.root);
    return xp;
}

Xpres Xpres::apply_function(std::string_view func_name) {
    this->root = create_node('f', exists(func_name, recognized_functions), this->root, nullptr);
    return *this;
}

Xpres Xpres::operator^(const Xpres & exp){
    operate_only_operator('^');
    token_info_f();
    return xp;
}

Xpres Xpres::operator%(const Xpres & exp){
    operate_only_operator('%');
    token_info_f();
    return xp;
}

Xpres Xpres::operator/(const Xpres & exp){
    operate_only_operator('/');
    token_info_f();
    return xp;
}

Xpres Xpres::operator*(const Xpres & exp){
    operate_multi_operator('*');
    token_info_f();
    return xp;
}

Xpres Xpres::operator+(const Xpres & exp){
    operate_multi_operator('+');
    token_info_f();
    return xp;
}

Xpres Xpres::operator<(const Xpres & exp){
    operate_only_operator('<');
    token_info_f();
    return xp;
}

Xpres Xpres::operator>(const Xpres & exp){
    operate_only_operator('>');
    token_info_f();
    return xp;
}

Xpres Xpres::operator&(const Xpres & exp){
    operate_multi_operator('&');
    token_info_f();
    return xp;
}

Xpres Xpres::operator|(const Xpres & exp){
    operate_multi_operator('|');
    token_info_f();
    return xp;
}

/*--------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------Iterator----------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------*/

Xpres::iterator& Xpres::iterator::operator!(){
    points.top() = create_node('p', '!', points.top());
    almost_empty_points();
    return *this;
}

Xpres::iterator& Xpres::iterator::operator-(){
    points.top() = create_node('p', '-', points.top());
    almost_empty_points();
    return *this;
}

Xpres::iterator& Xpres::iterator::operator~(){
    points.top() = create_node('p', '~', points.top());
    almost_empty_points();
    return *this;
}

Xpres::iterator& Xpres::iterator::apply_function(std::string_view func_name) {
    points.top() = create_node('f', exists(func_name, recognized_functions), points.top(), nullptr);
    almost_empty_points();
    return *this;
}

Xpres::iterator& Xpres::iterator::operator^(const Xpres & exp){
    operate_only_operator_iterator('^');
    almost_empty_points();
    return *this;
}

Xpres::iterator& Xpres::iterator::operator%(const Xpres & exp){
    operate_only_operator_iterator('%');
    almost_empty_points();
    return *this;
}

Xpres::iterator& Xpres::iterator::operator/(const Xpres & exp){
    operate_only_operator_iterator('/');
    almost_empty_points();
    return *this;
}

Xpres::iterator& Xpres::iterator::operator*(const Xpres & exp){
    operate_multi_operator_iterator('*');
    almost_empty_points();
    return *this;
}

Xpres::iterator& Xpres::iterator::operator+(const Xpres & exp){
    operate_multi_operator_iterator('+');
    almost_empty_points();
    return *this;
}

Xpres::iterator& Xpres::iterator::operator<(const Xpres & exp){
    operate_only_operator_iterator('<');
    almost_empty_points();
    return *this;
}

Xpres::iterator& Xpres::iterator::operator>(const Xpres & exp){
    operate_only_operator_iterator('>');
    almost_empty_points();
    return *this;
}

Xpres::iterator& Xpres::iterator::operator&(const Xpres & exp){
    operate_multi_operator_iterator('&');
    almost_empty_points();
    return *this;
}

Xpres::iterator& Xpres::iterator::operator|(const Xpres & exp){
    operate_multi_operator_iterator('|');
    almost_empty_points();
    return *this;
}
