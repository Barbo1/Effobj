#include "../../xpres.hpp"

Xpres::~Xpres() {
  delete_nodes(this->root);
  for (const auto& [name, type, data] : this->token_info) {
    free_pair({type, data});
  }
  this->token_info.clear();
}
