#include "../../xpres.hpp"

Xpres::iterator& Xpres::iterator::replace_token(std::string_view nold, std::string_view nnew) {
  uint64_t idold = 0;
  const uint64_t n = this->token_info.size();

  while (idold < n && std::get<0>(this->token_info[idold]) != nold) { idold++; }

  if (idold < n) {
    uint64_t i = 0;
    nodeEX root = get_root(this->points);
    nodeEX top = this->points.top();

    if (repetition_counter_outer(root, top, idold)) {
      this->token_info.push_back(std::make_tuple(std::string(nnew), '\0', nullptr));
      change_id(idold, n, top);
    } else {
      std::get<0>(this->token_info[idold]) = nnew;
    }
  }
  return *this;
}
