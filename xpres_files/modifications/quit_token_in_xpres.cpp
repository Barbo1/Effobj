#include "../../xpres.hpp"

Xpres& Xpres::quit_token(std::string_view name) {
  uint64_t idname = 0;
  const uint64_t n = this->token_info.size();

  while (idname < n && std::get<0>(this->token_info[idname]) != name) { idname++; }

  this->token_info.erase(this->token_info.begin() + idname);
  quit_token_aux(this->root, idname, true);

  return *this;
}
