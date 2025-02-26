#include "../../xpres.hpp"

Xpres::iterator& Xpres::iterator::operator=(iterator && it) {
  this->points = std::exchange (it.points, std::stack<nodeEX>());
  this->token_info = it.token_info;
  return *this;
}
