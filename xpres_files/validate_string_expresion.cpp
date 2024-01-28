
/*  This funcion take an string and return true if there is a valid expresion. 
 * */
bool validate_string_expresion(std::string_view sexp) {
    const unsigned n = sexp.size();
    unsigned i;
    int k;
    bool is_expresion;
    bool is_number;
    bool is_token;
    bool is_pres_oper;
    bool is_pres_parentheses;
    bool is_dot;
    char let;
    
    i = 0;
    k = 0;
    is_expresion = true;
    is_number = false;
    is_token = false;
    is_pres_oper = false;
    is_pres_parentheses = false;
    is_dot = false;
    while (is_expresion && k >= 0 && i < n) {
        let = sexp[i];
        if (let != ' ') {
            
            // well formed operands.
            if (let == '.') {
                if (is_token || is_dot) {
                    is_expresion = false;
                } else {
                    is_number = true;
                    is_dot = true;
                    is_pres_oper = false;
                    is_pres_parentheses = false;
                }
            } else if (let == '-') {
                is_number = false;
                is_token = false;
                is_pres_oper = true;
                is_pres_parentheses = false;
                is_dot = false;
            } else if (exists(let, binary_operators) != -1) {
                if (is_number || is_token || is_pres_parentheses) {
                    is_number = false;
                    is_token = false;
                    is_expresion = !is_pres_oper;
                    is_pres_oper = true;
                    is_dot = false;
                    is_pres_parentheses = false;
                } else {
                    is_expresion = false;
                }
            } else if (exists(let, unitary_operators) != -1) {
                if (is_number || is_token || is_pres_parentheses) {
                    is_expresion = false;
                } else {
                    is_number = false;
                    is_token = false;
                    is_pres_oper = true;
                    is_dot = false;
                    is_pres_parentheses = false;
                }
            } else if (is_character(let)) {
                is_pres_parentheses = false;
                is_pres_oper = false;
                if(is_digit(let)) {
                    is_number = true;
                } else {
                    is_token = true;
                }
                is_expresion = !(is_number && is_token);
            } else if (let == '(') {
                if (is_number) {
                    is_expresion = false;
                } else {
                    is_number = false;
                    is_pres_parentheses = false;
                    is_token = false;
                    is_dot = false;
                    is_pres_oper = false;
                    k++;
                }
            } else if (let == ')') {
                if (is_pres_oper) {
                    is_expresion = false;
                } else {
                    is_number = false;
                    is_token = false;
                    is_dot = false;
                    is_pres_oper = false;
                    is_pres_parentheses = true;
                    k--; 
                }
            } else {
                is_expresion = false;
            }
        }
        i++;
    }
    return k == 0 && is_expresion && !is_pres_oper;
}
