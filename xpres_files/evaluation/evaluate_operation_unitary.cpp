#include "../../xpres.hpp"

inline std::pair<char, void*> Xpres::evaluate_operator_unitary (
    std::pair<char, void*> op1, 
    const char ope
    ) {
  switch (ope) {
    case '!': {
        data_t * top = (data_t*) op1.second;
        switch (op1.first) {
            case 'i': {
                if (*top < 0) { goto end_def; }
                int res = 1;
                for (int i = 2; i <= *top; i++) {
                    res *= i;
                }
                *top = res;
                break;
            }
            case 'd': {
                double * a = (double *)op1.second;
                *a = (double)tgamma(*a + 1);
                break;
            }
            case 'm': {
                Matrix<data_t> * b = (Matrix<data_t> *) op1.second;
                op1.second = new double{static_cast<double>((*b).determinant())};
                op1.first = 'd';
                delete b;
                break;
            }
            case 'M': {
                Matrix<double> * b = (Matrix<double> *) op1.second;
                op1.second = new double{(*b).determinant()};
                op1.first = 'd';
                delete b;
                break;
            }
            case 'e': {
                Xpres * a = (Xpres*)op1.second;
                *a = !(*a);
                break;
            }
            default:
                goto end_def;
        }
        break;
    }

    case '~': {
        switch (op1.first) {
            case 'i':
            case 'd': {
                data_t * a = (data_t *) op1.second; 
                *a = ~(*a);
                break;
            }
            case 'm': {
                Matrix<data_t> * a = (Matrix<data_t> *) op1.second;
                Matrix<double> * b = new Matrix<double>((*a).invert());
                delete a;
                op1.second = (void *) b;
                break;
            }
            case 'M': {
                Matrix<double> * a = (Matrix<double> *) op1.second;
                *a = Matrix<double>((*a).invert());
                break;
            }
            case 'e': {
                Xpres * a = (Xpres *) op1.second;
                *a = ~(*a);
                break;
            }
            default:
                goto end_def;
        }
        break;
    }

    case '-': {
        switch (op1.first) {
            case 'i': {
                data_t * a = (data_t *) op1.second;
                *a = -(*a);
                break;
            }
            case 'd': {
                double * a = (double *) op1.second;
                *a = -(*a);
                break;
            }
            case 'm': {
                Matrix<data_t> * a = (Matrix<data_t> *) op1.second;
                *a = (*a)*(-1);
                break;
            }
            case 'M': {
                Matrix<double> * a = (Matrix<double> *) op1.second;
                *a = (*a)*(-1);
                break;
            }
            case 'e': {
                Xpres * a = (Xpres *) op1.second;
                *a = -(*a);
                break;
            }
            default:
                goto end_def;
        } 
        break;
    }
    default:
        goto end_def;
  }
  return op1;
  end_def:
  free_pair(op1);
  op1 = {'\0', (void*)nullptr};
  return op1;
}
