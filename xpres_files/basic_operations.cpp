
/*------------------------------------------------------------------------------------------*/
/*------------------------------------------Xpres-------------------------------------------*/
/*------------------------------------------------------------------------------------------*/

/* Default constructor.
 * */
Xpres::Xpres() {
    this->root = create_node(0, 0);
}

/* Constructor from a int.
 * */
Xpres::Xpres(int i) {
    this->root = create_node('i', i);
}

/* Constructor from a double.
 * */
Xpres::Xpres(double d) {
    this->root = create_node('d', d);
}

/* This is the constructor that make an expresion form a string.
 * Precondition: the string is a valid expresion, that menas,
 * validate_string_expresion(sexp) == true. 
 * */
Xpres::Xpres(std::string_view sexp) {
    double convdi; 
    int j;
    int curr;
    char let;
    unsigned i;
    unsigned n;
    unsigned last;
    unsigned top;
    bool is_number;
    bool is_hash;
    bool has_dot;
    nodeEX res_1;
    nodeEX res_2;
    std::string operand;
    std::vector<std::string> token_names;

    top = 1;
    for (i = 0; i < sexp.size(); i++) {
        if(sexp[i] == '(') {
            top++;
        }
    }

    std::string ret[top]{""};
    unsigned prev[top]{0};

    is_number = true;
    curr = 0;
    last = 0;
    j = 0;
    for (i = 0; i < sexp.size(); i++) {
        let = sexp[i];
        if (let != ' '){
            if(let == '(') {
                ret[curr] += (is_number ? '#' : '$') + std::to_string(last+1);
                prev[++j] = curr;
                curr = ++last;
                is_number = true;
            } else if (let == ')') {
                curr = prev[j--];
                is_number = false;
            } else {
                is_number = !is_character(let); 
                ret[curr] += let;
            }
        }
    }


    nodeEX fin[top]{nullptr};

    for (curr = top-1; curr >= 0; curr--) {
        char res;
        std::string current_str = ret[curr];
        std::stack<nodeEX> st_tok;
        std::stack<char> st_ope;
        
        i = 0;
        is_number = false;
        n = current_str.size();
 
        while (i < n) {
            operand = "";
            is_hash = false;
            let = current_str[i];
            if (let == '#') {
                is_hash = true;
                std::string res_str = "";
                let = current_str[++i];
                while(std::isdigit(let)) {
                    res_str += let;
                    let = current_str[++i];
                }
                operand = "#";
                st_tok.push(fin[atoi(res_str.c_str())]);
            } else if (is_character(let)) {
                is_number = is_digit(let);
                has_dot = let == '.';
                while (is_character(let)) {
                    has_dot |= let == '.';
                    operand += let;
                    let = current_str[++i];
                }
                if (is_number) {
                    if (has_dot) {
                        st_tok.push(create_node(
                            'd',
                            * (data_t *) &(convdi = atof(operand.c_str()))
                        ));
                    } else { 
                        st_tok.push(create_node('i', atoi(operand.c_str())));
                    }
                } else if (let == '$') {
                    std::string res_str = "";
                    let = current_str[++i];
                    while(std::isdigit(let)) {
                        res_str += let;
                        let = current_str[++i];
                    }
                    
                   // for now, it is assumed that the function is one of the recognized.
                    st_tok.push(create_node(
                                'f', 
                                exists<std::string_view>(operand, recognized_functions),
                                fin[atoi(res_str.c_str())],
                                nullptr)
                            );
                    continue;
                } else {
                    j = exists(operand, token_names);
                    if (j == -1) {
                        j = token_names.size();
                        token_names.push_back(operand);
                    }
                    st_tok.push(create_node('t', j));
                }
            }
            if (let != '\0') {
                while (!st_ope.empty() && (((res = st_ope.top()) == '-' && let == '-') || 
                          (precedence(res, let) > 0 && 
                           !(res == '@' && let == '~' || 
                            res == '!' && let == '~' || 
                            res == '!' && let == '-' && operand == "" || 
                            res == '@' && let == '-' && operand == "") 
                          ))) {
                    st_ope.pop();
                    res_1 = st_tok.top();
                    st_tok.pop();
                    if (res == '!' || res == '~' || res == '@') {
                        st_tok.push(create_node('p', res == '@' ? '-' : res, res_1, nullptr)); 
                    } else {
                        res_2 = st_tok.top();
                        st_tok.pop();
                        st_tok.push(deduce_operation_binary(res_2, res_1, res));
                    }
                }
                st_ope.push(operand == "" && let == '-' ? '@' : let);
            } 
            i++;
        }

        // consume the stacks.
        while (!st_ope.empty()) {
            res = st_ope.top();
            st_ope.pop();
            res_1 = st_tok.top();
            st_tok.pop();
            if (res == '!' || res == '~' || res == '@') {
                st_tok.push(create_node('p', res == '@' ? '-' : res, res_1, nullptr)); 
            } else {
                res_2 = st_tok.top();
                st_tok.pop();
                st_tok.push(deduce_operation_binary(res_2, res_1, res));
            }
        }
        fin[curr] = st_tok.top();
    }

    this->root = fin[0];

    for (auto it = token_names.begin(); it != token_names.end(); it++) {
        this->token_info.push_back({*it, '\0', nullptr});
    }
}

/* Copy constructor. 
 * */
Xpres::Xpres(const Xpres & exp) {
    this->root = copy_nodes(exp.root, false);
    for (const auto& [name, type, data] : exp.token_info) {
        this->token_info.push_back(std::make_tuple(name, type, copy_pair({type, data}).second));
    }
}

/* Move constructor. 
 * */
Xpres::Xpres(Xpres && exp) noexcept {
    this->root = std::exchange(exp.root, create_node(0, 0));
    this->token_info = std::exchange(exp.token_info, std::vector<std::tuple<std::string, char, void*>>());
}

/* Copy assignment. 
 * */
Xpres& Xpres::operator=(const Xpres & exp) noexcept {
    if(&exp != this) {
        delete_nodes(this->root);
        this->root = copy_nodes(exp.root);
        for (const auto& [name, type, data] : this->token_info) {
            free_pair({type, data});
        }
        this->token_info = exp.token_info;
    }
    return *this;
}

/* Move assignment. 
 * */
Xpres& Xpres::operator=(Xpres && exp) noexcept {
    if(&exp != this){
        delete_nodes(this->root);
        this->root = std::exchange(exp.root, create_node(0, 0));
        for (const auto& [name, type, data] : this->token_info) {
            free_pair({type, data});
        }
        this->token_info = std::exchange(
            exp.token_info, 
            std::vector<std::tuple<std::string, char, void*>>()
        );
    }
    return *this;
}

bool Xpres::operator==(const Xpres & exp) const noexcept {
    if (exp.token_info.size() != this->token_info.size()) { return false; }
    return compare_tree_similar(exp.root, this->root, this->token_info.size());
}

/* Destructor.
 * */
Xpres::~Xpres() {
    delete_nodes(this->root);
    for (const auto& [name, type, data] : this->token_info) {
        free_pair({type, data});
    }
    this->token_info.clear();
}


/*------------------------------------------------------------------------------------------*/
/*--------------------------------------iterator--------------------------------------------*/
/*------------------------------------------------------------------------------------------*/

/* Constructor by copy.
 * */
Xpres::iterator::iterator(Xpres & exp) : token_info(exp.token_info) {
    points.push(exp.root);
}

/* Copy constructor.
 * */
Xpres::iterator::iterator(const iterator & it) : token_info(it.token_info) {
    this->points = std::stack<nodeEX>(it.points);
}

/* Copy assignment.
 * */
Xpres::iterator& Xpres::iterator::operator=(const iterator & it) {
    this->points = std::stack<nodeEX>(it.points);
    this->token_info = it.token_info;
    return *this;
}

/* Move constructor.
 * */
Xpres::iterator::iterator(iterator && it) : token_info(it.token_info) {
    this->points = std::exchange (it.points, std::stack<nodeEX>());
}

/* Move assignment.
 * */
Xpres::iterator& Xpres::iterator::operator=(iterator && it) {
    this->points = std::exchange (it.points, std::stack<nodeEX>());
    this->token_info = it.token_info;
    return *this;
}
