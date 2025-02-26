#include "../../xpres.hpp"

std::string Xpres::to_string () const noexcept {
  return to_string_node (this->root, this->token_info);
}
