#include "../../worst.hpp"

WordSet::iterator WordSet::iterator::operator=(const iterator & it){
  _large_ = it._large_;
  _nodes_ = new nodeWS[MAX_LEN_WORD];
  for (int i = 0; i < _large_; i++) {
    _nodes_[i] = it._nodes_[i];
  }
  return *this;
}
