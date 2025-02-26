#include "../../xpres.hpp"

Xpres::iterator& Xpres::iterator::operator=(const iterator & it) {
  this->points = std::stack<nodeEX>(it.points);
  this->token_info = it.token_info;
  return *this;
}
