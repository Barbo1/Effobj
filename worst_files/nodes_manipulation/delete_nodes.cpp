#include "../../worst.hpp"

void WordSet::delete_nodes(nodeWS node){
  if (node != nullptr) {
    delete_nodes(node->sibling);
    delete_nodes(node->son);
    delete node;
  }
}
