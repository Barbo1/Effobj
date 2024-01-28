
/* Create a node with the specified data passed by parameter. */
static nodeEX inline create_node(uint8_t type, uint64_t id, nodeEX son = nullptr, nodeEX sibling = nullptr) {
    nodeEX new_node = new exp_struct;
    new_node->son = son;
    new_node-> sibling = sibling;
    new_node->type = type;
    new_node->id = id;
    return new_node;
}

/* Delete a node, and the nodes below and along it. */
static void delete_nodes(nodeEX node){
    if(node != nullptr){
        delete_nodes(node->sibling);
        delete_nodes(node->son); 
        delete node;
    }
}

/*
    Make a copy of the intern structure below a node of the Xpres and return it. If the 
    parameter not_same_level == false, the procedure also will copy the structure along.
*/
static nodeEX copy_nodes(nodeEX node, bool not_same_level = true){
    if(node == nullptr) {
        return nullptr;
    }
    nodeEX node_new = create_node(node->type, node->id, copy_nodes(node->son, false), nullptr);
    if(not_same_level) {
        node_new->sibling = nullptr;
    } else  {
        node_new->sibling = copy_nodes(node->sibling, false);
    }
    return node_new;
}

/* Add n to the id of each token node. */
void add_ids(nodeEX root, uint64_t n) {
    if (root != nullptr) {
        if (root->type == 't') {
            root->id += n;
        }
        add_ids (root->son, n);
        add_ids (root->sibling, n);
    }
}

/* Recalculate the token node's id depending on the array passed by parameter. */
static nodeEX recalculate_ids(nodeEX node, uint64_t * arr) { 
    if (node != nullptr) {
        if (node->type == 't') {
            node->id = arr[node->id];
        }
        recalculate_ids(node->son, arr);
        recalculate_ids(node->sibling, arr);
    }
    return node;
}

/* 
    Change the id of the tokens with id == idold to be idnew, in the 
    node below last_son (included). 
*/
void change_id(const uint64_t idold, const uint64_t idnew, nodeEX last_son) {
    if (last_son != nullptr) {
        if (last_son->type == 't' && last_son->id == idold) {
            last_son->id = idnew;
        }

        last_son = last_son->son;
        while (last_son != nullptr) {
            change_id(idold, idnew, last_son);
            last_son = last_son->sibling;
        }
    }
}

/* 
    Change the ocurrences of token nodes with id == idold with a copy of 
    node_exp tree, below last_son. Probably this function need to be 
    used after using recalculte_ids.
*/
bool change_tree(const uint64_t idold, nodeEX node_exp, nodeEX last_son) {
    if (last_son != nullptr) {
        if (last_son->type == 't' && last_son->id == idold) {
            return true;
        }

        nodeEX father = last_son;
        nodeEX last_son_prev = nullptr;
        nodeEX copia;
        last_son = last_son->son;
        while (last_son != nullptr) {
            if (change_tree(idold, node_exp, last_son)) {
                copia = copy_nodes(node_exp);
                if (last_son_prev != nullptr) {
                    last_son_prev->sibling = copia;
                } else {
                    father->son = copia;
                }
                copia->sibling = last_son->sibling;
                delete last_son;
                last_son_prev = copia;
                last_son = copia->sibling;
            } else {
                last_son_prev = last_son;
                last_son = last_son->sibling;
            }
        }
    }
    return false;
}

void repetition_counter_arr_aux(nodeEX root, const nodeEX last_son, uint64_t index, const uint64_t & length, bool * arr) {
    if (root == last_son) {
        index = length;
    }
    if (root != nullptr && root->type == 't') {
        arr[index + root->id] = true;
    }
    root = root->son;
    while (root != nullptr) {
        repetition_counter_arr_aux(root, last_son, index, length, arr);
        root = root->sibling;
    }
}

/* 
    This function returns a two dimentional array of 2 by length that contains:
        - true in the first row in the positions which index represent a node 
            outer the last_son subtree, false otherwise.
        - true in the second row in the positions which index represent a node 
            inner the last_son subtree, false otherwise.
*/
bool * repetition_counter_arr(nodeEX root, const nodeEX last_son, uint64_t length) {
    bool * arr = new bool[length * 2]{false};
    repetition_counter_arr_aux(root, last_son, 0, length, arr);
    return arr;
}

void repetition_counter_outer_arr_aux(nodeEX root, const nodeEX last_son, bool * arr) {
    if (root != last_son) {
        if (root->type == 't') {
            arr[root->id] = true;
        }
        root = root->son;
        while (root != nullptr) {
            repetition_counter_outer_arr_aux(root, last_son, arr);
            root = root->sibling;
        }
    }
}

/* 
    Returns an array that contains true in the positions which index represent 
    the id of the token nodes outer the last_son subtree, false otherwise.
*/
bool * repetition_counter_outer_arr(nodeEX root, const nodeEX last_son, uint64_t length) {
    bool * arr = new bool[length]{false};
    repetition_counter_outer_arr_aux(root, last_son, arr);
    return arr;
}

/* Returns true if outer token nodes has id == idold. */
bool repetition_counter_outer(nodeEX root, const nodeEX last_son, uint64_t idold) {
    if (root != last_son) {
        bool res = root->type == 't' && root->id == idold;

        root = root->son;
        while (!res && root != nullptr) {
            res = repetition_counter_outer(root, last_son, idold); 
            root = root->sibling;
        }
        return res;
    } else {
        return false;
    } 
}

/* Get a nodeEX and put it in the begining of the "sons array". The sontc need to be a son of father. */
void put_first (const nodeEX father, nodeEX sontc) {
    nodeEX prev = father->son;
    if (prev != sontc) {
        while (prev->sibling != sontc) {
            prev = prev->sibling;
        }
        prev->sibling = sontc->sibling;
        sontc->sibling = father->son;
        father->son = sontc;
    }
}

/* Get an array with the nodes that are sons of the 'father' node in order. */
std::vector<nodeEX> get_array_sons (nodeEX father) {
    std::vector<nodeEX> vec;
    vec.reserve (20);
    father = father->son;
    while (father != nullptr) {
        vec.push_back (father);
        father = father->sibling;
    }
    return vec;
}

bool compare_tree_similar_aux (nodeEX root1, nodeEX root2, uint64_t * arr, bool not_same_level = false) {
    if (root1 == nullptr || root2 == nullptr) { return root1 == nullptr && root2 == nullptr; }
    if (root1->type != root2->type || root1->id != root2->id) { return false; }
    if (root1->type == 't' && arr[root1->id] == 0) {
        arr[root1->id] = root2->id;
    } else if (root1->type == 'p' && is_oper_bm (root1->id)) {

        /* Get the sons of both trees. */
        nodeEX res;
        std::vector<nodeEX> arr1 = get_array_sons (root1);
        std::vector<nodeEX> arr2 = get_array_sons (root2);
        uint64_t len1 = arr1.size();
        if (len1 == 0 || len1 != arr2.size()) { 
            return false; 
        }

        /* Match pairs of nodes that represent equal subexpresions (they can be in a no straight order). */
        uint64_t j;
        for (uint64_t i = 0; i < len1; i++) {
            j = i;
            while (j < len1 && !compare_tree_similar_aux (arr1[i], arr2[j], arr)) {
                j++;
            }
            if (j == len1) {
                return false;
            }
            std::swap(arr2[i], arr2[j]);
        }

        return not_same_level || compare_tree_similar_aux (root1->sibling, root2->sibling, arr);

    }
    return 
        ((root1->type != 't' && root1->id == root2->id) || 
         (root1->type == 't' && (arr[root1->id] == 0 || arr[root1->id] == root2->id))) && 
        compare_tree_similar_aux (root1->son, root2->son, arr) && 
        (not_same_level || compare_tree_similar_aux (root1->sibling, root2->sibling, arr));
}

/* 
    Compare two trees to see if they represent the same expresion. That means that the names and values of two token 
    can be different but the expresion remains the same (i.e. "a + b*c"_exp = "r + q*r"_exp).
    Precondition: both trees have the same quantitys of tokens (max_id).
*/
bool compare_tree_similar (nodeEX root1, nodeEX root2, uint64_t max_id) {
    uint64_t arr[max_id]{0};
    return compare_tree_similar_aux (root1, root2, arr);
}

/*  
    Compare two trees to see if they are exactly the same. 
*/
bool compare_tree_equal (nodeEX root1, nodeEX root2, bool not_same_level = false) {
    if (root1 == nullptr || root2 == nullptr) { return root1 == nullptr && root2 == nullptr; }
    if (root1->type != root2->type || root1->id != root2->id) { return false; }
    if (root1->type == 'p' && is_oper_bm (root1->id)) {

        /* Get the sons of both trees. */
        nodeEX res;
        std::vector<nodeEX> arr1 = get_array_sons (root1);
        std::vector<nodeEX> arr2 = get_array_sons (root2);
        uint64_t len1 = arr1.size();
        if (len1 == 0 || len1 != arr2.size()) { 
            return false; 
        }

        /* Match pairs of nodes that represent equal subexpresions (they can be in a no straight order). */
        uint64_t j;
        for (uint64_t i = 0; i < len1; i++) {
            j = i;
            while (j < len1 && !compare_tree_equal(arr1[i], arr2[j])) {
                j++;
            }
            if (j == len1) {
                return false;
            }
            std::swap(arr2[i], arr2[j]);
        }

        return not_same_level || compare_tree_equal(root1->sibling, root2->sibling);

    } else {
        return compare_tree_equal (root1->son, root2->son) && 
            (not_same_level || compare_tree_equal (root1->sibling, root2->sibling));
    }
}
