#include "../../xpres.hpp"

Xpres::iterator::iterator(iterator && it) : expresion(it.expresion), token_info(it.token_info) {
  this->points = std::exchange (it.points, std::stack<nodeEX>());
}
