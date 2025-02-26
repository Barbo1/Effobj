#include "../../../xpres.hpp"

std::pair<char, void*> Xpres::copy_pair(std::pair<char, void*> op) {
  if (op.first == 'i') {
    op.second = (void *)(new data_t(* (data_t *) op.second));
  } else if (op.first == 'd') {
    op.second = (void *)(new double(* (double *) op.second));
  } else if (op.first == 'M') {
    op.second = (void *)(new Matrix<double>(* (Matrix<double> *) op.second));
  } else if (op.first == 'm') {
    op.second = (void *)(new Matrix<data_t>(* (Matrix<data_t> *) op.second));
  } else if (op.first == 'e') {
    op.second = (void *)(new Xpres(* (Xpres *) op.second));
  }
  return op;
}
