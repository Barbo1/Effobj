#include "../../xpres.hpp"

Xpres::iterator& Xpres::iterator::quit_token(std::string_view name) {
  uint64_t idname = 0;
  const uint64_t n = this->token_info.size();

  while (idname < n && std::get<0>(this->token_info[idname]) != name) { idname++; }

  bool res = repetition_counter_outer(get_root(this->points), this->points.top(), idname);

  if (res) { this->token_info.erase(this->token_info.begin() + idname); }
  quit_token_aux(this->points.top(), idname, res);

  return *this;
}

