#include "../../worst.hpp"

std::string WordSet::iterator::operator*() const {
  std::string str("");
  int i = 0;
  while (i <= _large_) {
    str += _nodes_[i++]->letter;
  }
  return str;
}
