#include "../../xpres.hpp"

Xpres::iterator::iterator(Xpres & exp) : expresion(exp), token_info(exp.token_info) {
  points.push(exp.root);
}
