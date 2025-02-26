#include "../../xpres.hpp"

Xpres& Xpres::replace_token(std::string_view nold, std::string_view nnew) {
  uint64_t idn = 0, idold = 0;
  const uint64_t n = this->token_info.size();

  while (idold < n && nold != std::get<0>(this->token_info[idold])) { idold++; }
  if (idold < n) {
    while (idn < n && nnew != std::get<0>(this->token_info[idn])) { idn++; }
    if (idn < n) {
      change_id (idold, idn, this->root);

      /* remove element from token_info. */
      const auto& [n0, n1, n2] = this->token_info[idold];
      free_pair (std::pair<char, void*>(n1, n2));
      this->token_info.erase (this->token_info.begin () + idold);

      /* recalculate ids. */
      uint64_t arr[n];
      for (idn = 0; idn < n; idn++) { arr[idn] = idn - (idn >= idold); }
      recalculate_ids (this->root, arr);
    } else {
      std::get<0>(this->token_info[idold]) = nnew;
    }
  }
  return *this;
}
