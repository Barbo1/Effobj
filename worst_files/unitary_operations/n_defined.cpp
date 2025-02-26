#include "../../worst.hpp"

/* Return a copy of the nodes that leads to, or follow, a node in the n-height
 * that have a 'letter' character, counting n below the node passed by parameter.
 * */
nodeWS WordSet::aux_n_defined (nodeWS node, unsigned len, char & letter, unsigned char & n) { 
  if (node != nullptr) {
    if (len < n) {
      /* son_i iterate for the sons of the node, constructing the node if
         at least one son return a copied node(copied in the elseif) */
      nodeWS son_i = node->son, sons = nullptr, res, son_f = nullptr;
      while (son_i != nullptr) {
        res = aux_n_defined(son_i, len+1, letter, n);
        if (res != nullptr) {
          sons = 
            (sons != nullptr ? sons->sibling : son_f) = 
              res;
        }
        son_i = son_i->sibling;
      }
      if (son_f != nullptr) {
        return create_node (
          node->letter,
          false,
          son_f,
          nullptr
        );
      }
    } else if (node->letter == letter) { // len == n &&
      return copy_nodes(node);
    }
  }
  return nullptr;
}

WordSet WordSet::n_defined(unsigned char position, char letter) const {
  WordSet tr = WordSet();
  nodeWS res = aux_n_defined(this->root, 0, letter, position);
  if (res != nullptr) {
    delete tr.root;
    tr.root = res;
  }
  return tr;
}
