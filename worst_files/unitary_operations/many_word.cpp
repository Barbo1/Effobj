#include "../../worst.hpp"

static unsigned aux_many_word (nodeWS node){
  if (node != nullptr) {
    return node->finished + aux_many_word(node->sibling) + aux_many_word(node->son);
  }
  return 0;
}

unsigned WordSet::many_word() const { 
  return aux_many_word (this->root);
}
