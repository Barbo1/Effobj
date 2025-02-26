#include "../../worst.hpp"

void WordSet::delete_word (WordSet::iterator & it){
  int i = it._large_;
  nodeWS nd = it._nodes_[i];
  nodeWS nd_father = it._nodes_[i-1];
  nd->finished = false;

  if (nd->son == nullptr) {
    while (i > 0 && !nd->finished && nd->sibling == nullptr && nd_father->son == nd) {
      delete nd;
      nd = it._nodes_[--i];
      nd_father = it._nodes_[i-1];
    }
    if (!nd->finished) {
      if (i == 0) {
        nd_father = this->root;
      }
      if (nd_father->son == nd) {
        nd_father->son = nd->sibling;
      } else {
        nd_father = nd_father->son;
        while (nd_father->sibling != nd) nd_father = nd_father->sibling;
        nd_father->sibling = nd->sibling;
      }
      delete nd;
    } else {
      nd->son = nullptr;
    }
  }
  it._large_ = -1;
}

