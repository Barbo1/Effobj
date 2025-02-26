#include "../../worst.hpp"

WordSet::WordSet (WordSet && tr) noexcept{
  if (&tr != this) {
    this->root = tr.root;
    tr.root = new node_word_set_struct;
    tr.root->letter = 0;
    tr.root->finished = false;
    tr.root->son = tr.root->sibling = nullptr;
  }
}
