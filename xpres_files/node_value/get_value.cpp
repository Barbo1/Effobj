#include "../../xpres.hpp"

std::pair<char, void*> Xpres::get_value(std::string_view name) {
  auto it = token_info.begin();
  while (it != token_info.end() && std::get<0>(*it) != name) {
    it++;
  }
  if (it == token_info.end()) {
    return {'\0', (void*)nullptr};
  } else {
    return {std::get<1>(*it), std::get<2>(*it)};
  }
}
