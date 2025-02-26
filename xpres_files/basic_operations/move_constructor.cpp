#include "../../xpres.hpp"

Xpres::Xpres(Xpres && exp) noexcept {
  this->root = std::exchange(exp.root, create_node(0, 0));
  this->token_info = std::exchange(exp.token_info, std::vector<std::tuple<std::string, char, void*>>());
}
