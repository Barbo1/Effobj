#include "../../worst.hpp"
#include <utility>

WordSet::iterator WordSet::find_word(const std::string & word) const {
  int i = 0, n = word.length();
  nodeWS tr_father = this->root;
  nodeWS tr = tr_father->son;
  WordSet::iterator it;

  while (tr != nullptr && i < n) {
    if (tr->letter == word[i]) [[unlikely]] {
      it._nodes_[i++] = tr;
      tr_father = std::exchange(tr, tr->son);
    } else [[likely]] {
      tr = tr->sibling;
    }
  }
  if (tr_father->finished && i == n) {
    it._large_ = i - 1;
  } else {
    delete [] it._nodes_;
  }
  return it;
}
