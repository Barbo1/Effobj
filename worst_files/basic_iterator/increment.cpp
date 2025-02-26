#include "../../worst.hpp"

WordSet::iterator& WordSet::iterator::operator++ () {
  nodeWS tr = _nodes_[_large_];
  if (tr->son != nullptr) {
    _nodes_[++_large_] = tr = tr->son;
  } else {
    while (_large_ >= 0 && _nodes_[_large_]->sibling == nullptr) {
      _large_--; 
    }
    if (_large_ < 0) {
      return *this;
    }
    tr = _nodes_[_large_] = _nodes_[_large_]->sibling;
  }
  while (tr->son != nullptr && !tr->finished) {
    _nodes_[++_large_] = tr = tr->son;
  }
  return *this;
}
