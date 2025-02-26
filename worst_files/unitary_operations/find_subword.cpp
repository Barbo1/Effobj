#include "../../worst.hpp"

nodeWS WordSet::aux_find_subword (nodeWS node, unsigned pos, const char * str, const int & n) { 
  if (node != nullptr) {
    if (pos < n || node->letter != str[pos]) {
      nodeWS son_i = node->son, sons = nullptr, res, son_f = nullptr;
      if (node->letter == str[pos]) pos++;
      else if (node->letter == str[0]) pos = 1;
      else pos = 0;
      while (son_i != nullptr) {
        res = aux_find_subword (son_i, pos, str, n);
        if(res != nullptr) {
          sons = 
            (sons != nullptr ? sons->sibling : son_f) = 
              res;
        }
        son_i = son_i->sibling;
      }
      if (son_f != nullptr) {
        return create_node (res->letter, false, son_f);
      }
    }
    return copy_nodes(node);
  }
  return nullptr;
}

WordSet WordSet::find_subword(const std::string & word) const {
  WordSet tr = WordSet();
  nodeWS res = aux_find_subword(this->root, 0, word.c_str(), word.length()-1);
  if (res != nullptr) {
    delete tr.root;
    tr.root = res;
  }
  return tr;
}
