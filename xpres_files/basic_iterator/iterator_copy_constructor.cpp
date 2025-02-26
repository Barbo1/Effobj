#include "../../xpres.hpp"

Xpres::iterator::iterator(const iterator & it) : expresion(it.expresion), token_info(it.token_info) {
  this->points = std::stack<nodeEX>(it.points);
}
