#include "../../worst.hpp"
#include <utility>

WordSet::iterator WordSet::iterator::operator=(iterator && it){
  _large_ = std::exchange(it._large_, -1);
  for (int i = 0; i < _large_; i++) {
    _nodes_[i] = it._nodes_[i];
  }
  return *this;
}
