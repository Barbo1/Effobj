
// This operation is used to create nodes and/or put them in proper order.
// precondition 1: op belongs to operators.
// clarification: op is the operator from the stack of operators, and the others 
// are from the stack of operands.
static nodeEX deduce_operation_binary (nodeEX res_1, nodeEX res_2, const char op) {
    nodeEX res;
    uint8_t ids = (res_1->type != 'p') | ((res_2->type != 'p') << 1);

    switch (ids) {
        // both are types.
        case 3:
            res = create_node('p', op == '-' ? '+' : op , res_1, nullptr);
            if (op == '-') { 
                res_2 = create_node('p', '-', res_2, nullptr);
            }
            res_1->sibling = res_2;
            break;
        
        // res_1 is a operator && res_2 is an type. 
        case 2:
            if (op == '-') {
                res_2 = create_node('p', op, res_2, nullptr);
                if (res_1->id == '+') {
                    res = std::exchange (res_1, res_1->son);
                    while(res_1->sibling != nullptr) {
                        res_1 = res_1->sibling;
                    }
                } else {
                    res = create_node('p', '+', res_1, nullptr);
                }
            } else if (res_1->id == op && is_oper_bm (op)) { 
                res = std::exchange (res_1, res_1->son);
                while(res_1->sibling != nullptr) {
                    res_1 = res_1->sibling;
                }
            } else {
                res = create_node('p', op, res_1, nullptr);
            }
            res_1->sibling = res_2;
            break;
        
        // res_1 is a type && res_2 is an operator . 
        case 1:
            if (op == '-') {
                if (res_2->id == '+') {
                    res = std::exchange (res_2, res_2->son);
                    res->son = res_1;
                    res_1->sibling = res_2;
                    while(res_1->sibling != nullptr) {
                        res_1 = res_1->sibling = create_node('p', '-', res_1->sibling, nullptr);
                    }
                } else {
                    res = create_node('p', '+', res_1, nullptr);
                    res_1->sibling = create_node('p', '-', res_2, nullptr);
                }

            } else if (res_2->id == op && is_oper_bm (op)) {
                res = res_2;
                res_1->sibling = std::exchange (res_2->son, res_1);

            } else {
                res = create_node('p', op, res_1, nullptr);
                res_1->sibling = res_2;
            }
            break;

        // both are operators (op never will be '-', except the last one) .
        case 0:
            if (res_1->id == op && res_2->id == op) {
                if (is_oper_bm (op)) {
                    res = std::exchange (res_1, res_1->son);
                    while(res_1->sibling != nullptr) {
                        res_1 = res_1->sibling;
                    }
                    res_1->sibling = res_2->son;
                    delete res_2;
                } else {
                    res = create_node('p', op, res_1, nullptr);
                    res_1->sibling = res_2;
                }

            } else if (res_1->id == op && res_2->id != op) {
                if (is_oper_bm (op)) { 
                    res = std::exchange (res_1, res_1->son);
                    while(res_1->sibling != nullptr) {
                        res_1 = res_1->sibling;
                    }
                } else {
                    res = create_node('p', op, res_1, nullptr);
                }
                res_1->sibling = res_2;

            } else if (res_1->id != op && res_2->id == op) {
                if (is_oper_bm (op)) {
                    res = res_2;
                    res_1->sibling = std::exchange(res_2->son, res_1);
                } else {
                    res = create_node('p', op, res_1, nullptr);
                    res_1->sibling = res_2;
                }

            } else {
                if (op == '-') {
                    if (res_1->id == '+') {
                        res = res_1;
                        res_1 = res_1->son;
                        while(res_1->sibling != nullptr) {
                            res_1 = res_1->sibling;
                        }
                    } else {
                        res = create_node('p', '+', res_1, nullptr);
                    }
                    if (res_2->id == '+') {
                        res_1->sibling = res_2->son;
                        delete res_2;
                        res_2 = res_1->sibling;
                        while (res_2 != nullptr) {
                            res_2 = create_node('p', '-', res_2, nullptr);
                            res_2 = res_2->sibling;
                        }
                    } else {
                        res_1->sibling = create_node('p', '-', res_2, nullptr);
                    }
                } else {
                    res = create_node('p', op, res_1, nullptr);
                    res_1->sibling = res_2;
                }
            }
            break;
    }
    return res;
}
