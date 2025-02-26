#include "../../xpres.hpp"

Xpres::Xpres(const Xpres & exp) {
  this->root = copy_nodes(exp.root, false);
  for (const auto& [name, type, data] : exp.token_info) {
    this->token_info.push_back(std::make_tuple(name, type, copy_pair({type, data}).second));
  }
}
