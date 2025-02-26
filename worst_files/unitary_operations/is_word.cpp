#include "../../worst.hpp"
#include <utility>

bool WordSet::is_word(const std::string & word) const {
  int i = 0, n = word.length();
  nodeWS tr_father = this->root;
  nodeWS tr = tr_father->son;

  while (tr != nullptr && i < n) {
    if (tr->letter == word[i++]) [[unlikely]] tr_father = std::exchange(tr, tr->son);
    else [[likely]] tr = tr->sibling;
  }
  return tr_father->finished && i == n;
}
