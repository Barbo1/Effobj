
/* This function is meant to make the evaluation of two operands with the passed operator 'ope'.
 * It will work only for unary operators (the next function is for binary).
 * */
inline std::pair<char, void*> evaluate_operator_binary(
        std::pair<char, void*> op1, 
        std::pair<char, void*> op2, 
        const char ope
    ) {
    if (op1.first == 'i' && op2.first == 'i') {
        long int * a = (long int*)op1.second; 
        switch (ope) {
            case '^':
                *a = std::pow(*a, * (long int*) op2.second);
                break;
            case '%':
                *a = (*a) % (* (long int*) op2.second);
                break;
            case '/':
                *a = (*a) / (* (long int*) op2.second);
                break;
            case '*':
                *a = (*a) * (* (long int*) op2.second);
                break;
            case '+':
                *a = (*a) + (* (long int*) op2.second);
                break;
            case '<':
                *a = (*a) << (* (long int*) op2.second);
                break;
            case '>':
                *a = ((*a) >> (* (long int*) op2.second));
                break;
            case '&':
                *a = (*a) & (* (long int*) op2.second);
                break;
            case '|':
                *a = (*a) | (* (long int*) op2.second);
                break;
            default:
                free_pair(op2);
                free_pair(op1);
                return {'\0', (void*)nullptr};    
                break;
        }
        free_pair(op2);
    } else if (op1.first == 'i' && op2.first == 'd') {
        double * a = (double *)op2.second;
        switch (ope) {
            case '^':
                *a = std::pow(* (long int*) op1.second, *a);
                break;
            case '/':
                *a = (double)(* (long int*) op1.second) / (*a);
                break;
            case '*':
                *a = (* (long int*) op1.second) * (*a);
                break;
            case '+':
                *a = (double)(* (long int*) op1.second) + (*a);
                break;
            case '&': {
                long int r = (* (long int*) op1.second) | (* (long int *) a);
                *a = * (double *) &r;
                break;
            }
            case '|': {
                long int r = (* (long int*) op1.second) & (* (long int *) a);
                *a = * (double *) &r;
                break;
            }
            default:
                free_pair(op2);
                free_pair(op1);
                return {'\0', (void*)nullptr};    
                break;
        }
        exchange_pair(op1, op2);
        free_pair(op2);
    } else if (op1.first == 'd' && op2.first == 'i') {
        double * a = (double *)op1.second;
        switch (ope) {
            case '^':
                *a = std::pow(*a, * (long int*) op2.second);
                break;
            case '/':
                *a = (*a) / (double)(* (long int*) op2.second);
                break;
            case '*':
                *a *= (double)(* (long int*) op2.second);
                break;
            case '+':
                *a += (double)(* (long int*) op2.second);
                break;
            case '<': {
                long int r = (* (long int *) a) << (* (long int*) op2.second);
                *a = * (double*) &r;
                break;
            }
            case '>': {
                long int r = (* (long int *) a) >> (* (long int*) op2.second);
                *a = * (double*) &r;
                break;
            }
            case '&': {
                long int r = (* (long int *) a) & (* (long int*) op2.second);
                *a = * (double*) &r;
                break;
            }
            case '|': {
                long int r = (* (long int *) a) | (* (long int*) op2.second);
                *a = * (double*) &r;
                break;
            }
            default:
                free_pair(op2);
                free_pair(op1);
                return {'\0', (void*)nullptr};    
                break;
        }
        free_pair(op2);
    } else if (op1.first == 'd' && op2.first == 'd') {
        double * a = (double *)op1.second;
        switch (ope) {
            case '^':
                *a = std::pow(*a, * (double*) op2.second);
                break;
            case '/':
                *a = (*a) / (* (double*) op2.second);
                break;
            case '*':
                *a = (*a) * (* (double*) op2.second);
                break;
            case '+':
                *a = (*a) + (* (double*) op2.second);
                break;
            case '&':
                {
                    long int r = (* (long int *) a) & (* (long int*) op2.second);
                    *a = * (double*) &r;
                    break;
                }
            case '|':
                {
                    long int r = (* (long int *) a) | (* (long int*) op2.second);
                    *a = * (double*) &r;
                    break;
                }
            default:
                free_pair(op2);
                free_pair(op1);
                return {'\0', (void*)nullptr};    
                break;
        }
        free_pair(op2);
    } else if (op1.first == 'm' && op2.first == 'm') {
        Matrix<long int> * a = (Matrix<long int> *)op1.second;
        switch (ope) {
            case '*':
                *a = (*a) * (* (Matrix<long int> *) op2.second);
                break;
            case '+':
                *a = (*a) + (* (Matrix<long int> *) op2.second);
                break;
            default:
                free_pair(op2);
                free_pair(op1);
                return {'\0', (void*)nullptr};    
                break;
        }
        free_pair(op2);
    } else if (op1.first == 'M' && op2.first == 'm') {
        Matrix<double> * a = (Matrix<double> *)op1.second;
        switch (ope) {
            case '*':
                *a = (*a) * (* (Matrix<long int> *) op2.second).cast<double>();
                break;
            case '+':
                *a = (*a) + (* (Matrix<long int> *) op2.second).cast<double>();
                break;
            default:
                free_pair(op2);
                free_pair(op1);
                return {'\0', (void*)nullptr};    
                break;
        }
        free_pair(op2);
    } else if (op1.first == 'm' && op2.first == 'M') {
        Matrix<double> * a = (Matrix<double> *)op2.second;
        switch (ope) {
            case '*':
                *a = (* (Matrix<long int> *) op1.second).cast<double>() * (*a);
                break;
            case '+':
                *a = (* (Matrix<long int> *) op1.second).cast<double>() + (*a);
                break;
            default:
                free_pair(op2);
                free_pair(op1);
                return {'\0', (void*)nullptr};    
                break;
        }
        exchange_pair(op1, op2);
        free_pair(op2);
    } else if (op1.first == 'M' && op2.first == 'M') {
        Matrix<double> * a = (Matrix<double> *)op1.second;
        switch (ope) {
            case '*':
                *a = (*a) * (* (Matrix<double> *) op2.second);
                break;
            case '+':
                *a = (*a) + (* (Matrix<double> *) op2.second);
                break;
            default:
                free_pair(op2);
                free_pair(op1);
                return {'\0', (void*)nullptr};    
                break;
        }
        free_pair(op2);
    } else if (op1.first == 'e' && op2.first == 'e') {
        Xpres * a = (Xpres *)op1.second;
        switch (ope) {
            case '^':
                *a = (*a) ^ (* (Xpres *) op2.second);
                break;
            case '%':
                *a = (*a) % (* (Xpres *) op2.second);
                break;
            case '/':
                *a = (*a) / (* (Xpres *) op2.second);
                break;
            case '*':
                *a = (*a) * (* (Xpres *) op2.second);
                break;
            case '+':
                *a = (*a) + (* (Xpres *) op2.second);
                break;
            case '<':
                *a = (*a) < (* (Xpres *) op2.second);
                break;
            case '>':
                *a = (*a) > (* (Xpres *) op2.second);
                break;
            case '&':
                *a = (*a) & (* (Xpres *) op2.second);
                break;
            case '|':
                *a = (*a) | (* (Xpres *) op2.second);
                break;
            default:
                free_pair(op2);
                free_pair(op1);
                return {'\0', (void*)nullptr};    
                break;
        }
        free_pair(op2);
    } else { 
        free_pair(op2);
        free_pair(op1);
        op1 = {'\0', (void*)nullptr};    
    }

    return op1;
}

