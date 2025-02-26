#include "../../worst.hpp"

WordSet::WordSet () {
  this->root = new node_word_set_struct;
  this->root->letter = 0;
  this->root->finished = false;
  this->root->son = this->root->sibling = nullptr;
}
