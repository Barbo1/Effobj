#include "../../worst.hpp"

bool WordSet::iterator::operator== (const iterator & it) const {
  if (it._large_ != _large_) return false;
  int i = 0;
  while (i <= _large_ && it._nodes_[i] == _nodes_[i]) i++;
  return i > _large_;
}
