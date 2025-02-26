#include "../../xpres.hpp"

Xpres& Xpres::operator=(Xpres && exp) noexcept {
  if(&exp != this){
    delete_nodes(this->root);
    this->root = std::exchange(exp.root, create_node(0, 0));
    for (const auto& [name, type, data] : this->token_info) {
      free_pair({type, data});
    }
    this->token_info = std::exchange(
        exp.token_info, 
        std::vector<std::tuple<std::string, char, void*>>()
        );
  }
  return *this;
}
