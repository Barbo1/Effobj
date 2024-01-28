
Xpres& Xpres::replace_token(std::string_view nold, const Xpres & exp) {
    uint64_t idold = 0, i;
    const uint64_t size_this = this->token_info.size();

    while (idold < size_this && nold != std::get<0>(this->token_info[idold])) { 
        idold++; 
    }

    if (idold < size_this) {
        const uint64_t size_exp = exp.token_info.size();

        /* 
            Generating an array that contain true in a position if the token is in both exp and                        
            this. If the repited id is the one to be replaced, will be false. 
        */
        bool _ids[exp.token_info.size()]{};
        for (const auto& [n1, _, __]: exp.token_info) {
            for (i = 0; i < size_this; i++) {
                if (n1 == std::get<0>(this->token_info[i])) {
                    _ids[i] = i != idold;
                    goto new_iteration;
                }
            }
            new_iteration:
        }

        /* Remove idold from token_info. */
        const auto& [name, type, data] = this->token_info[idold];
        free_pair (std::pair<char, void*>(type, data));
        this->token_info.erase (this->token_info.begin() + idold);

        int64_t n = size_this-1;

        /* Generating an array _new_ids empty to put ids to change. */
        uint64_t _new_ids[size_this];
        for (i = 0; i < size_this; i++) {
            _new_ids [i] = (i == idold ? n : i) - (i > idold);
        }
        recalculate_ids (this->root, _new_ids);

        /* Make a copy of the exp with all the ids plus n. */
        nodeEX root = copy_nodes (exp.root);
        add_ids (root, n);
        change_tree (n, root, this->root);
        delete_nodes (root);
        
        /* Add the missing tokens to this. */
        i = 0;
        for (const auto& [name, type, data]: exp.token_info) {
            this->token_info.push_back (
                make_tuple (
                    _ids[i] ? get_new_name (name) : name,
                    type, 
                    data 
                )
            );
            i++;
        }
    }
    return *this;
}

Xpres& Xpres::replace_token(std::string_view nold, std::string_view nnew) {
    uint64_t idn = 0, idold = 0;
    const uint64_t n = this->token_info.size();

    while (idold < n && nold != std::get<0>(this->token_info[idold])) { idold++; }
    if (idold < n) {
        while (idn < n && nnew != std::get<0>(this->token_info[idn])) { idn++; }
        if (idn < n) {
            change_id (idold, idn, this->root);

            /* remove element from token_info. */
            const auto& [n0, n1, n2] = this->token_info[idold];
            free_pair (std::pair<char, void*>(n1, n2));
            this->token_info.erase (this->token_info.begin () + idold);

            /* recalculate ids. */
            uint64_t arr[n];
            for (idn = 0; idn < n; idn++) { arr[idn] = idn - (idn >= idold); }
            recalculate_ids (this->root, arr);
        } else {
            std::get<0>(this->token_info[idold]) = nnew;
        }
    }
    return *this;
}

Xpres::iterator& Xpres::iterator::operator[](int64_t index) {
    nodeEX son = this->points.top()->son;
    if (index >= 0) {
        while (son != nullptr && index-- > 0) { son = son->sibling; }
        if (son != nullptr) { this->points.push(son); }
    } else {
        while (!this->points.empty() && index++ < 0) { this->points.pop(); }
    }
    return *this;
}

Xpres::iterator& Xpres::iterator::compose(uint64_t id_1, uint64_t id_2, std::string_view name) {
    nodeEX top = this->points.top();
    if (top->type == 'p' && top->id == '+' && id_1 != id_2) {

        /* finding the id of name. */
        uint64_t id_name = 0;
        for (const auto & [n1, n2, n3]: this->token_info) {
            if (n1 == name) { goto finded; }
            id_name++;
        }
        return *this;
        finded:

        if (id_1 > id_2) { std::swap (id_1, id_2); }
        nodeEX son;

        /* finding the first node. */
        son = top->son;
        while (son != nullptr && id_1 != 0) {
            id_1--;
            id_2--;
            son = son->sibling;
        }
        if (son == nullptr) return *this;
        nodeEX son1 = son;

        /* finding the second node. */
        son = son->sibling;
        id_2--;
        while (son != nullptr && id_2 != 0) {
            id_2--;
            son = son->sibling;
        }
        if (son == nullptr) return *this;
        nodeEX son2 = son;
        
        /* lambda functions. */
        auto cond0 = [&id_name](const nodeEX n){
            return n->type == 't' && n->id == id_name;
        };
        auto cond1 = [&](const nodeEX n){
            return n->type == 'p' && n->id == '*';
        };
        auto cond2 = [&](const nodeEX n){
            return n->type == 'p' && n->id == '/';
        };
        auto cond3 = [&](const nodeEX n){
            return n->type == 'p' && n->id == '-';
        };

        /* evaluate lambda conditions. */
        nodeEX son1c = son1, son2c = son2;
        if (cond3 (son1c)) {
            son1c = son1c->son;
        }
        if (cond3 (son2c)) {
            son2c = son2c->son;
        }
        uint16_t conds1 = cond0(son1c) | (cond1(son1c)<<1) | (cond2(son1c)<<2);
        uint16_t conds2 = cond0(son2c) | (cond1(son2c)<<1) | (cond2(son2c)<<2);
        if (!conds1 || !conds2) return *this;

        /* operations. */
        auto find_token = [&son, &id_name] (const nodeEX father) mutable {
            son = father->son;
            while (son != nullptr && (son->type != 't' || son->id != id_name)) {
                son = son->sibling;
            }
            return son;
        };
        auto quit_node = [](const nodeEX father, const nodeEX son) {
            put_first(father, son);
            if (son->sibling->sibling == nullptr) {
                father->type = son->sibling->type;
                father->id = son->sibling->id;
                father->son = son->sibling->son;
                son->sibling->son = nullptr;
                delete son->sibling;
            } else {
                father->son = son->sibling;
                son->sibling = nullptr;
            }
            delete son;
        };

        /* 
            the switch divides the cases depending on the most presedent operator
            of both the expresions to compose.
        */
        nodeEX son11, son21;
        switch (conds1 | (conds2 << 3)) {
            /* two tokens. */
            case 0b001001:
                son1c->type = 'i';
                son1c->id = 1;
                son2c->type = 'i';
                son2c->id = 1;
                break;

            /* multiplication and token. */
            case 0b010001:
                std::swap (son1c, son2c);
            case 0b001010:
                if ((son11 = find_token (son1c)) == nullptr) return *this;
                
                quit_node (son1c, son11);
                son2c->type = 'i';
                son2c->id = 1;
                break;
            
            /* division and token. */
            case 0b100001:
                std::swap (son1c, son2c);
            case 0b001100:
                son11 = son1c->son;
                if (cond0 (son11)) {
                    son11->type = 'i';
                    son11->id = 1;
                } else if (cond1 (son11) && (son11 = find_token (son11)) != nullptr) {
                    quit_node (son1c->son, son11);
                } else { 
                    return *this; 
                }
                son2c->type = 'i';
                son2c->id = 1;
                break;

            /* two multiplications. */
            case 0b010010:
                son11 = find_token (son1c);
                son21 = find_token (son2c);

                if (son11 == nullptr || son21 == nullptr) return *this;

                quit_node (son2c, son21);
                quit_node (son1c, son11);
                break;
            
            /* division and multiplication. */
            case 0b100010:
                std::swap (son1c, son2c);
            case 0b010100:
                son21 = find_token (son2c);
                son11 = son1c->son;
                conds1 = cond0 (son11) | ((cond1 (son11) && (son11 = find_token (son11)) != nullptr) << 1);
                if (!conds1 || son21 == nullptr) { return *this; }
                switch (conds1) {
                    case 1:
                        son11->type = 'i';
                        son11->id = 1;
                        break;
                    case 2:
                        quit_node (son1c->son, son11);
                        break;
                    default:
                        return *this; 
                        break;
                }
                quit_node (son2c, son21);

                break;

            /* two divisions. */
            case 0b100100:
                son11 = son1c->son;
                son21 = son2c->son;
                conds1 = cond0 (son11) | ((cond1 (son11) && (son11 = find_token (son11)) != nullptr) << 1);
                conds2 = cond0 (son21) | ((cond1 (son21) && (son21 = find_token (son21)) != nullptr) << 1);
                if (!conds1 || !conds2) { return *this; }
                switch (conds1) {
                    case 1:
                        son11->type = 'i';
                        son11->id = 1;
                        break;
                    case 2:
                        quit_node (son1c->son, son11);
                        break;
                    default:
                        return *this; 
                        break;
                }
                switch (conds2) {
                    case 1:
                        son21->type = 'i';
                        son21->id = 1;
                        break;
                    case 2:
                        quit_node (son2c->son, son21);
                        break;
                    default:
                        return *this; 
                        break;
                }
                break;

            default:
                return *this;
                break;
        }
        put_first(top, son2);
        put_first(top, son1);
        if (son2->sibling == nullptr) {
            top->id = '*';
            const nodeEX _news = create_node ('t', id_name, nullptr, create_node ('p', '+'));
            _news->sibling->son = std::exchange (top->son, _news);

            if (this->points.size() < 2) { return *this; }
            this->points.pop();
            nodeEX prev_top = this->points.top();
            if (prev_top->type != 'p' || prev_top->id != '*') {
                this->points.push(top);
                return *this; 
            }
            son = prev_top->son;
            if (son == top) {
                _news->sibling->sibling = top->sibling;
                prev_top->son = _news;
            } else {
                while (son->sibling != top) {
                    son = son->sibling;
                }
                _news->sibling->sibling = top->sibling;
                son->sibling = _news;
            }
            delete top;

            /* When I try to use the same iterator that is returned from this function, it throws a memory 
             * error. By now it is not posible to utilize it. */

        } else {
            top->son = create_node (
                'p', 
                '*', 
                create_node ('t', id_name), 
                std::exchange (son2->sibling, nullptr)
            );
            son1->sibling = nullptr;
            top->son->son->sibling = deduce_operation_binary (son1, son2, '+');
        }
    }
    return *this;
}


/* This will change when I have an array instead of a stack. */
inline nodeEX get_root (std::stack<nodeEX> st_this) {
    nodeEX root;

    while (!st_this.empty()) {
        root = st_this.top();
        st_this.pop();
    }
 
    return root;
}

Xpres::iterator& Xpres::iterator::descompose(uint64_t id_1 = 0, uint64_t id_2 = 1) {
    nodeEX top = this->points.top();
    if (top->type == 'p' && id_1 != id_2) {

        /* discerning element to decompose over. */
        bool over_2 = id_1 > id_2;
        if (over_2) { std::swap (id_1, id_2); } 
        nodeEX son;

        /* finding the first node. */
        son = top->son;
        while (son != nullptr && id_1 != 0) {
            id_1--;
            id_2--;
            son = son->sibling;
        }
        if (son == nullptr) return *this;
        nodeEX son1 = son;

        /* finding the second node. */
        son = son->sibling;
        id_2--;
        while (son != nullptr && id_2 != 0) {
            id_2--;
            son = son->sibling;
        }
        if (son == nullptr) return *this;
        nodeEX son2 = son;

        if (over_2) { std::swap (son1, son2); }

        /* discriminating cases: */
        nodeEX sum;
        switch (top->id) {
            case '*':
                if (son1->type != 'p') { return *this; }
                switch (son1->id) {
                    case '+':
                        sum = son1;
                        break;
                    case '-':
                    case '/':
                        sum = son1->son;
                        while (sum != nullptr && sum->type == 'p' && sum->id == '-') { sum = sum->son; }
                        if (sum == nullptr || sum->type != 'p' || sum->id != '+') { return *this; }
                        break;
                    default:
                        return *this;
                }
                break;
            case '/':
                sum = son1;
                while (sum != nullptr && sum->type == 'p' && sum->id == '-') { sum = sum->son; }
                if (sum == nullptr || sum->type != 'p' || sum->id != '+') { return *this; }
                break;
            default:
                return *this;
        }
        fin_switch:
       
        /* change tree. */
        nodeEX sum1 = sum->son;
        nodeEX prev = nullptr, sib;
        while (sum1 != nullptr) {
            sib = std::exchange (sum1->sibling, nullptr);
            sum1 = 
                (prev == nullptr ? sum->son : prev->sibling) = 
                    deduce_operation_binary (
                        (over_2 ? copy_nodes (son2) : sum1), 
                        (over_2 ? sum1 : copy_nodes (son2)), 
                        top->id
                    );
            sum1->sibling = sib;
            prev = std::exchange (sum1, sum1->sibling);
        }
        
        /* keep the expression valid. */
        put_first(top, son2);
        top->son = son2->sibling;
        son2->sibling = nullptr;
        delete_nodes (son2);

        if (top->son == son1 && son1->sibling == nullptr && !is_oper_u(top->id)) {
            top->id = son1->id;
            top->type = son1->type;
            nodeEX _news = top->son = son1->son;
            delete son1;

            if (this->points.size() < 2) { return *this; }
            this->points.pop();
            nodeEX prev_top = this->points.top();
            if (prev_top->type != 'p' || prev_top->id != '+' || top->type != 'p' || top->id != '+') {
                this->points.push(top);
                return *this;
            }
            son = prev_top->son;
            if (son == top) {
                _news->sibling->sibling = top->sibling;
                prev_top->son = _news;
            } else {
                while (son->sibling != top) {
                    son = son->sibling;
                }
                _news->sibling->sibling = top->sibling;
                son->sibling = _news;
            }
            delete top;

            /* When I try to use the same iterator that is returned from this function, it throws a memory
             * error. By now it is not posible to utilize it. */
        }
    }
    return *this;
}

Xpres::iterator& Xpres::iterator::potence(uint64_t id_1, uint64_t id_2) {
    nodeEX top = this->points.top();
    if (top->type == 'p' && top->id == '*' && id_1 != id_2) {
        if (id_1 > id_2) { std::swap (id_1, id_2); } 

        /* finding the first node. */
        nodeEX son1 = top->son;
        while (son1 != nullptr && id_1 != 0) {
            id_1--;
            id_2--;
            son1 = son1->sibling;
        }
        if (son1 == nullptr) return *this;

        /* finding the second node. */
        nodeEX son2 = son1->sibling;
        id_2--;
        while (son2 != nullptr && id_2 != 0) {
            id_2--;
            son2 = son2->sibling;
        }
        if (son2 == nullptr) return *this;

        bool c1 = son1->type == 'p' && son1->id == '^';
        bool c2 = son2->type == 'p' && son2->id == '^';

        /* there are four cases. */
        if (c1 && c2) {
            if (!compare_tree_equal(son1->son, son2->son, true)) { return *this; }
            
            /* put first both. */
            put_first (top, son2);
            put_first (top, son1);

            top->son = son2;
            son2->son->sibling = deduce_operation_binary(son1->son->sibling, son2->son->sibling, '+');
            son1->son->sibling = nullptr;
            delete_nodes (son1->son);
            delete son1;

        } else if (c1) {
            if (!compare_tree_equal(son1->son, son2, true)) { return *this; }
            
            /* put first both. */
            put_first (top, son2);
            put_first (top, son1);

            son1->son->sibling = deduce_operation_binary(son1->son->sibling, create_node ('i', 1), '+');
            son1->sibling = son2->sibling;
            son2->sibling = nullptr;
            delete_nodes (son2);

        } else if (c2) {
            if (!compare_tree_equal(son2->son, son1, true)) { return *this; }
            
            /* put first both. */
            put_first (top, son1);
            put_first (top, son2);

            son2->son->sibling = deduce_operation_binary(son2->son->sibling, create_node ('i', 1), '+');
            son2->sibling = son1->sibling;
            son1->sibling = nullptr;
            delete_nodes (son1);

        } else if (compare_tree_equal(son2, son1, true)) {
            /* put first both. */
            put_first (top, son2);
            put_first (top, son1);
           
            if (son2->sibling == nullptr) {
                top->id = '^';
            } else {
                top->son = create_node ('p', '^', son1, son2->sibling);
                son2->sibling = nullptr;
            }
            son2->type = 'i';
            son2->id = 2;
        }
    }
    return *this;
}

Xpres::iterator& Xpres::iterator::depotence() {
    nodeEX top = this->points.top();
    if (top->type == 'p' && top->id == '^') {
        nodeEX res = top->son->sibling;
        if (res->type != 'p' || res->id != '+') return *this;

        /* Transforma all the sons of res and put them in the begining of top. */
        nodeEX cop = top->son;
        nodeEX son = res->son;
        nodeEX prev = nullptr;
        top->id = '*';
        top->son = nullptr;
        cop->sibling = nullptr;

        delete res;
        while (son->sibling != nullptr) {
            top->son = create_node ('p', '^', copy_nodes (cop), top->son);
            top->son->son->sibling = prev = son;
            son = son->sibling;
            prev->sibling = nullptr;
        } 
        top->son = create_node ('p', '^', cop, top->son);
        top->son->son->sibling = son;

        /* Restruct the tree. */
        this->points.pop();
        res = this->points.top();
        if (res->type == 'p' && res->id == '*') {
            /* Quit top from the tree. */

            son = res->son;
            if (son == top) {
                res->son = top->sibling;
            } else {
                while (son->sibling != top) {
                    son = son->sibling;
                }
                son->sibling = top->sibling;
            }

            /* Find the lastest son. */
            while (son->sibling != nullptr) {
                son = son->sibling;
            }

            son->sibling = top->son;
            delete top;
        } else {
            this->points.push(top);
        }
    }
    return *this;
}

/*
    Take the root of a tree(or a subtree) and quit the token nodes that contain
    an id == idname. If recalculate_ids == true then the nodes with id > idname 
    will be decremented in one.
*/
bool quit_token_aux(nodeEX root, const uint64_t idname, bool recalculate_ids) {
    if (root->type == 't') {
        if (recalculate_ids && root->id > idname) {
            root->id--;
            return false;
        } else {
            return root->id == idname;
        }
    } else if (root->son != nullptr) {
        nodeEX son = root->son;
        nodeEX prev = nullptr;
        nodeEX res;
        while (son != nullptr) {
            if (quit_token_aux(son, idname, recalculate_ids)) {
                res = son;
                son = son->sibling;
                if (res->son != nullptr) {
                    (prev == nullptr ? root->son : prev->sibling) = res->son;
                    res->son->sibling = son;
                } else {
                    (prev == nullptr ? root->son : prev->sibling) = son;
                }
                delete res;
            } else {
                prev = son;
                son = son->sibling;
            }
        }
        return root->son->sibling == nullptr && !(
            root->type == 'p' && (root->id == '-' || root->id == '!' || root->id == '|') ||
            root->type == 'f'
        );
    }
    return false;
}

Xpres& Xpres::quit_token(std::string_view name) {
    uint64_t idname = 0;
    const uint64_t n = this->token_info.size();

    while (idname < n && std::get<0>(this->token_info[idname]) != name) { idname++; }
    
    this->token_info.erase(this->token_info.begin() + idname);
    quit_token_aux(this->root, idname, true);

    return *this;
}

Xpres::iterator& Xpres::iterator::quit_token(std::string_view name) {
    uint64_t idname = 0;
    const uint64_t n = this->token_info.size();

    while (idname < n && std::get<0>(this->token_info[idname]) != name) { idname++; }
    
    bool res = repetition_counter_outer(get_root(this->points), this->points.top(), idname);

    if (res) { this->token_info.erase(this->token_info.begin() + idname); }
    quit_token_aux(this->points.top(), idname, res);

    return *this;
}

Xpres::iterator& Xpres::iterator::replace_current(const Xpres & exp) {
    const uint64_t n = this->token_info.size();
    const nodeEX root = get_root(this->points);
    
    bool * tokens_bool = repetition_counter_arr(root, this->points.top(), n);

    uint64_t i = 0;
    uint64_t j;
    uint64_t new_id = n;
    std::vector<uint64_t> arr;
    std::string str;

    arr.reserve(exp.token_info.size());
    for (i = 0; i < exp.token_info.size(); i++) {
        str = std::get<0>(exp.token_info[i]);
        j = 0;
        while (j < n && str != std::get<0>(this->token_info[j])) {
            j++;
        }
   
        auto res = copy_pair(std::pair<char, void*>(std::get<1>(exp.token_info[i]), std::get<2>(exp.token_info[i])));
        if (j != n) {
            if (tokens_bool[j]) {
                arr.push_back(new_id++);
                this->token_info.push_back(std::make_tuple(get_new_name(str), res.first, res.second));
            } else {
                arr.push_back(j);
                free_pair(std::pair<char, void*>(std::get<1>(this->token_info[j]), std::get<2>(this->token_info[j])));
                this->token_info[j] = std::make_tuple(str, res.first, res.second);
            }
        } else {
            arr.push_back(new_id++);
            this->token_info.push_back(std::make_tuple(str, res.first, res.second));
        }
    }

    nodeEX copia = recalculate_ids(copy_nodes(exp.root), &arr[0]);
    nodeEX res = this->points.top();

    this->points.pop();
    if (!this->points.empty()) {
        nodeEX father = this->points.top();
        copia->sibling = res->sibling;
        if (father->son == res) {
            father->son = copia;
        } else {
            father = father->son;
            while (father->sibling != res) {
                father = father->sibling;
            }
            father->sibling = copia;
        }
        res->sibling = nullptr;
    }
    this->points.push(copia);
    delete_nodes(res);

    arr.clear();
    arr.reserve(new_id);
    j = 0;
    for (i = 0; i < n; i++) {
        if (tokens_bool[i] || !tokens_bool[n + i]) {
            if (j < i) { 
                this->token_info[j] = this->token_info[i]; 
            }
            arr.push_back(j);
            j++;
        } else {
            arr.push_back(0);
        }
    }
    for (; i < new_id; i++, j++) {
        this->token_info[j] = this->token_info[i];
        arr.push_back(j);
    }
    for (; new_id > n; new_id--) {
        this->token_info.pop_back();
    }

    recalculate_ids(root, &arr[0]);
    
    delete [] tokens_bool;
    return *this;
}

Xpres::iterator& Xpres::iterator::replace_token(std::string_view nold, const Xpres & exp) {
    uint64_t idold = 0;
    const uint64_t n = this->token_info.size();

    while (idold < n && std::get<0>(this->token_info[idold]) != nold) {
        idold++;
    }
    
    if (idold != n) {
        nodeEX root = get_root(this->points);
        bool * tokens_bool = repetition_counter_outer_arr(root, this->points.top(), n);
        uint64_t l_exp = exp.token_info.size();
        uint64_t i = 0;
        uint64_t j;
        uint64_t new_id = n;
        std::vector<uint64_t> arr;
        std::string str;
        while (i < l_exp) {
            str = std::get<0>(exp.token_info[i]);
            j = 0;
            while (j < n && str != std::get<0>(this->token_info[j])) {
                j++;
            }

            auto res = copy_pair(std::pair<char, void*>(std::get<1>(exp.token_info[i]), std::get<2>(exp.token_info[i])));
            if (j != n) {
                if (str != nold || tokens_bool[idold]) {
                    arr.push_back(new_id++);
                    this->token_info.push_back(std::make_tuple(get_new_name(str), res.first, res.second));
                } else {
                    free_pair(std::pair<char, void*>(std::get<1>(this->token_info[j]), std::get<2>(this->token_info[j])));
                    arr.push_back(j);
                    this->token_info[j] = std::make_tuple(str, res.first, res.second);
                }
            } else {
                arr.push_back(new_id++);
                this->token_info.push_back(std::make_tuple(str, res.first, res.second));
            }
            i++;
        }
    
        delete [] tokens_bool;

        nodeEX copia = recalculate_ids(copy_nodes(exp.root), &arr[0]);
        change_tree(idold, copia, this->points.top());
        delete_nodes(copia);
    }
    return *this;
}

Xpres::iterator& Xpres::iterator::replace_token(std::string_view nold, std::string_view nnew) {
    uint64_t idold = 0;
    const uint64_t n = this->token_info.size();

    while (idold < n && std::get<0>(this->token_info[idold]) != nold) { idold++; }
    
    if (idold < n) {
        uint64_t i = 0;
        nodeEX root = get_root(this->points);
        nodeEX top = this->points.top();

        if (repetition_counter_outer(root, top, idold)) {
            this->token_info.push_back(std::make_tuple(std::string(nnew), '\0', nullptr));
            change_id(idold, n, top);
        } else {
            std::get<0>(this->token_info[idold]) = nnew;
        }
    }
    return *this;
}

