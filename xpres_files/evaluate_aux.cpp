
std::pair<char, void*> evaluate_aux(
        nodeEX node,
        const std::vector<std::tuple<std::string, char, void*>> & token_info
    ) {
    nodeEX first_son = node->son;
    if (node->type == '\0') {
        return {'\0', nullptr};
    } else if (first_son == nullptr) {
        if (node->type == 't') {
            const auto & [name, type, data] = token_info[node->id];
            return copy_pair({type, data});
        } else {
            return {node->type, (void*) new data_t {node->id}};
        }
    } else {
        std::pair<char, void*> op1 = evaluate_aux(first_son, token_info);
        if (node->type == 'p') {
            if (is_oper_u(node->id)) {
                op1 = evaluate_operator_unitary(op1, node->id);
            } else {
                first_son = first_son->sibling;
                while (first_son != nullptr && first_son->type != '\0') {
                    op1 = evaluate_operator_binary(op1, evaluate_aux(first_son, token_info), node->id);
                    first_son = first_son->sibling;
                }
            }
        } else { 
            op1 = evaluate_function(op1, recognized_functions[node->id]);
        }
        return op1;
    }
}
