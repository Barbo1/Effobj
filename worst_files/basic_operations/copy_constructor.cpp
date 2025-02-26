#include "../../worst.hpp"

WordSet::WordSet(const WordSet & tr){
  if (&tr != this) this->root = copy_nodes(tr.root); 
}
