#include "../../../xpres.hpp"

/* Deallocate the memory of the void*, depending on the char.
 * */
void Xpres::free_pair (std::pair<char, void*> op) {
  if (op.first == 'i') {
    delete (data_t *)op.second;
  } else if (op.first == 'd') {
    delete (double *)op.second;
  } else if (op.first == 'M') {
    delete (Matrix<double> *)op.second;
  } else if (op.first == 'm') {
    delete (Matrix<data_t> *)op.second;
  } else {
    delete (Xpres *)op.second;
  }
}
