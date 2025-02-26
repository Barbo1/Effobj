#include "../../xpres.hpp"

inline std::pair<char, void*> Xpres::evaluate_operator_binary(
    std::pair<char, void*> op1, 
    std::pair<char, void*> op2, 
    const char ope
    ) {
  if (op1.first == 'i' && op2.first == 'i') {
    data_t * a = (data_t*)op1.second; 
    switch (ope) {
      case '^':
        *a = std::pow(*a, * (data_t*) op2.second);
        break;
      case '%':
        *a = (*a) % (* (data_t*) op2.second);
        break;
      case '/':
        *a = (*a) / (* (data_t*) op2.second);
        break;
      case '*':
        *a = (*a) * (* (data_t*) op2.second);
        break;
      case '+':
        *a = (*a) + (* (data_t*) op2.second);
        break;
      case '<':
        *a = (*a) << (* (data_t*) op2.second);
        break;
      case '>':
        *a = ((*a) >> (* (data_t*) op2.second));
        break;
      case '&':
        *a = (*a) & (* (data_t*) op2.second);
        break;
      case '|':
        *a = (*a) | (* (data_t*) op2.second);
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
        *a = std::pow(* (data_t*) op1.second, *a);
        break;
      case '/':
        *a = (double)(* (data_t*) op1.second) / (*a);
        break;
      case '*':
        *a = (* (data_t*) op1.second) * (*a);
        break;
      case '+':
        *a = (double)(* (data_t*) op1.second) + (*a);
        break;
      case '&': {
                  data_t r = (* (data_t*) op1.second) | (* (data_t *) a);
                  *a = * (double *) &r;
                  break;
                }
      case '|': {
                  data_t r = (* (data_t*) op1.second) & (* (data_t *) a);
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
        *a = std::pow(*a, * (data_t*) op2.second);
        break;
      case '/':
        *a = (*a) / (double)(* (data_t*) op2.second);
        break;
      case '*':
        *a *= (double)(* (data_t*) op2.second);
        break;
      case '+':
        *a += (double)(* (data_t*) op2.second);
        break;
      case '<': {
                  data_t r = (* (data_t *) a) << (* (data_t*) op2.second);
                  *a = * (double*) &r;
                  break;
                }
      case '>': {
                  data_t r = (* (data_t *) a) >> (* (data_t*) op2.second);
                  *a = * (double*) &r;
                  break;
                }
      case '&': {
                  data_t r = (* (data_t *) a) & (* (data_t*) op2.second);
                  *a = * (double*) &r;
                  break;
                }
      case '|': {
                  data_t r = (* (data_t *) a) | (* (data_t*) op2.second);
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
          data_t r = (* (data_t *) a) & (* (data_t*) op2.second);
          *a = * (double*) &r;
          break;
        }
      case '|':
        {
          data_t r = (* (data_t *) a) | (* (data_t*) op2.second);
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
    Matrix<data_t> * a = (Matrix<data_t> *)op1.second;
    switch (ope) {
      case '*':
        *a = (*a) * (* (Matrix<data_t> *) op2.second);
        break;
      case '+':
        *a = (*a) + (* (Matrix<data_t> *) op2.second);
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
        *a = (*a) * (* (Matrix<data_t> *) op2.second).cast<double>();
        break;
      case '+':
        *a = (*a) + (* (Matrix<data_t> *) op2.second).cast<double>();
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
        *a = (* (Matrix<data_t> *) op1.second).cast<double>() * (*a);
        break;
      case '+':
        *a = (* (Matrix<data_t> *) op1.second).cast<double>() + (*a);
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

