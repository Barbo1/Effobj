#include "../../xpres.hpp"

Xpres& Xpres::replace_token(std::string_view nold, const Xpres & exp) {
  uint64_t idold = 0, i;
  const uint64_t size_this = this->token_info.size();

  while (idold < size_this && nold != std::get<0>(this->token_info[idold])) { 
    idold++; 
  }

  if (idold < size_this) {

    /* Generating an array that contain true in a position if the token is in both exp and                        
     * this. If the repited id is the one to be replaced, will be false. 
     * */
    bool _ids[exp.token_info.size()];
    for (const auto& [n1, _, __]: exp.token_info) {
      for (i = 0; i < size_this; i++) {
        if (n1 == std::get<0>(this->token_info[i])) {
          _ids[i] = i != idold;
          goto new_iteration;
        }
      }
    new_iteration:
    }

    /* Remove idold from token_info. */
    const auto& [name, type, data] = this->token_info[idold];
    free_pair (std::pair<char, void*>(type, data));
    this->token_info.erase (this->token_info.begin() + idold);

    int64_t n = size_this-1;

    /* Generating an array _new_ids empty to put ids to change. */
    uint64_t _new_ids[size_this];
    for (i = 0; i < size_this; i++) {
      _new_ids [i] = (i == idold ? n : i) - (i > idold);
    }
    recalculate_ids (this->root, _new_ids);

    /* Make a copy of the exp with all the ids plus n. */
    nodeEX root = copy_nodes (exp.root);
    add_ids (root, n);
    change_tree (n, root, this->root);
    delete_nodes (root);

    /* Add the missing tokens to this. */
    i = 0;
    for (const auto& [name, type, data]: exp.token_info) {
      this->token_info.push_back (
        make_tuple (
          _ids[i] ? get_new_name (name) : name,
          type, 
          data 
          )
        );
      i++;
    }
  }
  return *this;
}
