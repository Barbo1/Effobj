#include "../../worst.hpp"

WordSet::iterator::iterator (const iterator& it) {
  _large_ = it._large_;
  for (int i = 0; i < _large_; i++) {
    _nodes_[i] = it._nodes_[i];
  }
}
