
/*--------------------------------------Xpres needed functions----------------------------------------*/

/* Return the final Xpres. Precondition: is_oper_m (oper) .*/
Xpres& operate_operator(const char oper, Xpres& xp, const Xpres& exp) {
    nodeEX prin = copy_nodes(exp.root);
    
    std::vector<uint64_t> vecc;
    const uint64_t n = xp.token_info.size();
    uint64_t cont = n, i;
    for (auto elem: exp.token_info) {
        const auto& [name, _, __] = elem;
        i = 0;
        while (i < n && std::get<0>(xp.token_info[i]) != name) {
            i++;
        }
        if (i == n) {
            xp.token_info.push_back (elem);
            vecc.push_back (cont++);
        } else {
            vecc.push_back (i);
        }
    }
    recalculate_ids (prin, &vecc[0]);
    
    if (oper == '-') {
        xp.root = deduce_operation_binary (xp.root, create_node ('p', '-', prin), '+');
    } else if (is_oper_bm(oper)) {
        xp.root = deduce_operation_binary (xp.root, prin, oper);
    } else {
        xp.root->sibling = prin;
        xp.root = create_node('p', oper, xp.root);
    }
    return xp;
}

/*--------------------------------------iterator needed functions----------------------------------------*/

void almost_empty_points(std::stack<nodeEX>& points) {
    if (points.size() > 1) {
        points.pop();
    }
}

void operate_operator_iterator(const char oper, Xpres::iterator& it, const Xpres& exp) { 
    nodeEX curr = it.points.top();
    nodeEX prin = copy_nodes(exp.root, false);
    
    std::vector<uint64_t> vecc;
    const uint64_t n = it.token_info.size();
    uint64_t cont = n, i;
    for (auto elem: exp.token_info) {
        const auto& [name, _, __] = elem;
        i = 0;
        while (i < n && std::get<0>(it.token_info[i]) != name) {
            i++;
        }
        if (i == n) {
            it.token_info.push_back (elem);
            vecc.push_back (cont++);
        } else {
            vecc.push_back (i);
        }
    }
    recalculate_ids (prin, &vecc[0]);

    if (it.points.size() > 1) {
        it.points.pop();
        nodeEX prev = it.points.top(), sib;
        if (prev->son == curr) {
            sib = std::exchange (curr->sibling, nullptr);
            prev->son = deduce_operation_binary (curr, prin, oper);
            prev->son->sibling = sib;
        } else {
            prev = prev->son;
            while (prev->sibling != curr) {
                prev = prev->sibling;
            }
            sib = std::exchange (curr->sibling, nullptr);
            prev->sibling = deduce_operation_binary (curr, prin, oper);
            prev->sibling->sibling = sib;
        }
    } else {
        prin = deduce_operation_binary (create_node (curr->type, curr->id, curr->son), prin, oper);
        nodeEX& res = it.points.top();
        res->type = prin->type; 
        res->id = prin->id; 
        res->son = prin->son; 
        res->sibling = nullptr;;
    }
}

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

Xpres Xpres::operator-=(const Xpres & exp) {
    return operate_operator('-', *this, exp);
}

Xpres Xpres::operator/=(const Xpres & exp) {
    return operate_operator('/', *this, exp);
}

Xpres Xpres::operator+=(const Xpres & exp) {
    return operate_operator('+', *this, exp);
}

Xpres Xpres::operator*=(const Xpres & exp) {
    return operate_operator('*', *this, exp);
}

Xpres Xpres::operator-(const Xpres & exp) {
    Xpres xp = Xpres(*this);
    return operate_operator('-', xp, exp);
}

Xpres Xpres::operator^(const Xpres & exp) {
    Xpres xp = Xpres(*this);
    return operate_operator('^', xp, exp);
}

Xpres Xpres::operator%(const Xpres & exp) {
    Xpres xp = Xpres(*this);
    return operate_operator('%', xp, exp);
}

Xpres Xpres::operator/(const Xpres & exp) {
    Xpres xp = Xpres(*this);
    return operate_operator('/', xp, exp);
}

Xpres Xpres::operator*(const Xpres & exp) {
    Xpres xp = Xpres(*this);
    return operate_operator('*', xp, exp);
}

Xpres Xpres::operator+(const Xpres & exp) {
    Xpres xp = Xpres(*this);
    return operate_operator('+', xp, exp);
}

Xpres Xpres::operator<(const Xpres & exp) {
    Xpres xp = Xpres(*this);
    return operate_operator('<', xp, exp);
}

Xpres Xpres::operator>(const Xpres & exp) {
    Xpres xp = Xpres(*this);
    return operate_operator('>', xp, exp);
}

Xpres Xpres::operator&(const Xpres & exp) {
    Xpres xp = Xpres(*this);
    return operate_operator('&', xp, exp);
}

Xpres Xpres::operator|(const Xpres & exp) {
    Xpres xp = Xpres(*this);
    return operate_operator('|', xp, exp);
}

/*--------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------Iterator----------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------*/

Xpres::iterator& Xpres::iterator::operator!() {
    points.top() = create_node('p', '!', points.top());
    almost_empty_points(this->points);
    return *this;
}

Xpres::iterator& Xpres::iterator::operator-() {
    points.top() = create_node('p', '-', points.top());
    almost_empty_points(this->points);
    return *this;
}

Xpres::iterator& Xpres::iterator::operator~() {
    points.top() = create_node('p', '~', points.top());
    almost_empty_points(this->points);
    return *this;
}

Xpres::iterator& Xpres::iterator::apply_function(std::string_view func_name) {
    points.top() = create_node('f', exists(func_name, recognized_functions), points.top(), nullptr);
    almost_empty_points(this->points);
    return *this;
}

Xpres::iterator& Xpres::iterator::operator-(const Xpres & exp) {
    points.top() = create_node('p', '-', points.top());
    almost_empty_points(this->points);
    return *this;
}

Xpres::iterator& Xpres::iterator::operator^(const Xpres & exp) {
    operate_operator_iterator('^', *this, exp);
    return *this;
}

Xpres::iterator& Xpres::iterator::operator%(const Xpres & exp) {
    operate_operator_iterator('%', *this, exp);
    return *this;
}

Xpres::iterator& Xpres::iterator::operator/(const Xpres & exp) {
    operate_operator_iterator('/', *this, exp);
    return *this;
}

Xpres::iterator& Xpres::iterator::operator*(const Xpres & exp) {
    operate_operator_iterator('*', *this, exp);
    return *this;
}

Xpres::iterator& Xpres::iterator::operator+(const Xpres & exp) {
    operate_operator_iterator('+', *this, exp);
    return *this;
}

Xpres::iterator& Xpres::iterator::operator<(const Xpres & exp) {
    operate_operator_iterator('<', *this, exp);
    return *this;
}

Xpres::iterator& Xpres::iterator::operator>(const Xpres & exp) {
    operate_operator_iterator('>', *this, exp);
    return *this;
}

Xpres::iterator& Xpres::iterator::operator&(const Xpres & exp) {
    operate_operator_iterator('&', *this, exp);
    return *this;
}

Xpres::iterator& Xpres::iterator::operator|(const Xpres & exp) {
    operate_operator_iterator('|', *this, exp);
    return *this;
}

