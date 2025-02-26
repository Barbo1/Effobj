#include "../../worst.hpp"

unsigned char WordSet::aux_get_largest(nodeWS node, unsigned char m) {
  if (node != nullptr) {
    unsigned a = aux_get_largest(node->son, m+1), b = aux_get_largest(node->sibling, m);
    return b > a ? b : a;
  }
  return m;
}

void WordSet::aux_ordered_by_length (
    nodeWS node, 
    std::string str, 
    unsigned char m, 
    std::vector<std::string> * vt
    ) {
  if (node != nullptr) {
    aux_ordered_by_length (node->sibling, str, m, vt);
    if (node->letter != 0) {
      str += node->letter;
    }
    if (node->finished) {
      vt[m-1].push_back (str);
    }
    aux_ordered_by_length(node->son, str, m+1, vt);
  }
}

std::vector<std::string> WordSet::ordered_by_length () const {
  int i = 0, n = aux_get_largest(this->root->son, 0);
  std::vector<std::string> * vt = new std::vector<std::string>[n];
  std::vector<std::string> vt_new;

  aux_ordered_by_length(this->root, "", 0, vt);
  for (int i = 0; i < n; i++) {
    vt_new.insert (vt_new.end(), vt[i].begin(), vt[i].end());
  }

  delete [] vt;
  return vt_new;
}
