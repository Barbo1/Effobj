#include "../../xpres.hpp"

Xpres& Xpres::operator=(const Xpres & exp) noexcept {
  if(&exp != this) {
    delete_nodes(this->root);
    this->root = copy_nodes(exp.root);
    for (const auto& [name, type, data] : this->token_info) {
      free_pair({type, data});
    }
    this->token_info = exp.token_info;
  }
  return *this;
}
