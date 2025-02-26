#include "../../worst.hpp"
#include <utility>

WordSet::iterator::iterator (iterator&& it) {
  delete [] _nodes_;
  _large_ = std::exchange(it._large_, -1); 
  _nodes_ = std::exchange(it._nodes_, nullptr);
}
