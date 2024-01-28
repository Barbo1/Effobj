
/*  precondition: op1 and op2 are operators. Returns 0 if both are the same
 *  operator, 1 of first operator have more precedence, and -1 in other case.
 * */
int precedence(char op1, char op2) {
    uint64_t i = 0, j = 0;
    while (operators[i] != op1) {i++;}
    while (operators[j] != op2) {j++;}
    if (i == j) {
        return 0;
    } else if (i > j) {
        return 1;
    } else {
        return -1;
    }
}

/* Return true if a char is a valid character. 
 * */
bool is_character(char let) {
    return std::isalnum(let) || let == '_' || let == '.';
}

/* Return true if a char belongs to a number representation. 
 * */
bool is_digit(char let) {
    return std::isdigit(let) || let == '.';
}

/* exchange the char and the void* of the two parameters.
 * */
void exchange_pair(std::pair<char, void*> & op1, std::pair<char, void*> & op2) {
    char a = op1.first;
    op1.first = op2.first;
    op2.first = a;

    void * b = op1.second;
    op1.second = op2.second;
    op2.second = b;
}

/* Deallocate the memory of the void*, depending on the char.
 * */
void free_pair(std::pair<char, void*> op1) {
    if (op1.first == 'i') {
        delete (data_t *)op1.second;
    } else if (op1.first == 'd') {
        delete (double *)op1.second;
    } else if (op1.first == 'M') {
        delete (Matrix<double> *)op1.second;
    } else if (op1.first == 'm') {
        delete (Matrix<data_t> *)op1.second;
    } else {
        delete (Xpres *)op1.second;
    }
}

std::pair<char, void*> copy_pair(std::pair<char, void*> op1) {
    if (op1.first == 'i') {
        op1.second = (void *)(new data_t(* (data_t *) op1.second));
    } else if (op1.first == 'd') {
        op1.second = (void *)(new double(* (double *) op1.second));
    } else if (op1.first == 'M') {
        op1.second = (void *)(new Matrix<double>(* (Matrix<double> *) op1.second));
    } else if (op1.first == 'm') {
        op1.second = (void *)(new Matrix<data_t>(* (Matrix<data_t> *) op1.second));
    } else if (op1.first == 'e') {
        op1.second = (void *)(new Xpres(* (Xpres *) op1.second));
    }
    return op1;
}

/* This funciton search an element in a vector and return true if it is in. 
 * */
template<typename T>
int exists(T var, std::vector<T> vec) {
    uint64_t i = 0;
    uint64_t n = vec.size();
    while (i < n && vec[i] != var) {
        i++;
    }
    if (i == n) {
        return -1;
    } else {
        return i;
    }
}

/* Quit an element, passed by parameter, from the vector. 
 * */
template<typename T>
void quit_from(T var, std::vector<T> vec) {
    auto it = vec.begin();
    while (it != vec.end() && *it != var) {
        it++;
    }
    if (it != vec.end()) {
        vec.erase(it);
    }
} 

/*
    This method will take the token_info array and will give a new std::string 
    with a name different of all other tokens. Now this give one based in the
    repited name, and can be repeated in another token.
*/
std::string get_new_name(std::string str) {
    return str + "_";
}

/* Returns true if the operator passed by parameter is a binary multioperator. */
bool is_oper_bm (uint8_t op) { 
    return exists((char)op, binary_multi_operators) != -1; 
}

/* Returns true if the operator passed by parameter is a binary (no multioperator). */
bool is_oper_b (uint8_t op) { 
    return exists((char)op, binary_nomulti_operators) != -1; 
}

/* Returns true if the operator passed by parameter is a unitary. */
bool is_oper_u (uint8_t op) { 
    return exists((char)op, unitary_operators) != -1; 
}
