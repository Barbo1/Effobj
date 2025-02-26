#include "../../worst.hpp"

WordSet & WordSet::operator=(const WordSet & tr){
  if (&tr != this) {
    delete_nodes(this->root);
    this->root = copy_nodes(tr.root);
  }
  return *this;
}
