#include "../../xpres.hpp"

Xpres::iterator& Xpres::iterator::replace_token(std::string_view nold, const Xpres & exp) {
  uint64_t idold = 0;
  const uint64_t n = this->token_info.size();

  while (idold < n && std::get<0>(this->token_info[idold]) != nold) {
    idold++;
  }

  if (idold != n) {
    nodeEX root = get_root(this->points);
    bool * tokens_bool = repetition_counter_outer_arr(root, this->points.top(), n);
    uint64_t l_exp = exp.token_info.size();
    uint64_t i = 0;
    uint64_t j;
    uint64_t new_id = n;
    std::vector<uint64_t> arr;
    std::string str;
    while (i < l_exp) {
      str = std::get<0>(exp.token_info[i]);
      j = 0;
      while (j < n && str != std::get<0>(this->token_info[j])) {
        j++;
      }

      auto res = copy_pair(std::pair<char, void*>(std::get<1>(exp.token_info[i]), std::get<2>(exp.token_info[i])));
      if (j != n) {
        if (str != nold || tokens_bool[idold]) {
          arr.push_back(new_id++);
          this->token_info.push_back(std::make_tuple(this->expresion.get_new_name(str), res.first, res.second));
        } else {
          free_pair(std::pair<char, void*>(std::get<1>(this->token_info[j]), std::get<2>(this->token_info[j])));
          arr.push_back(j);
          this->token_info[j] = std::make_tuple(str, res.first, res.second);
        }
      } else {
        arr.push_back(new_id++);
        this->token_info.push_back(std::make_tuple(str, res.first, res.second));
      }
      i++;
    }

    delete [] tokens_bool;

    nodeEX copia = recalculate_ids(copy_nodes(exp.root), &arr[0]);
    change_tree(idold, copia, this->points.top());
    delete_nodes(copia);
  }
  return *this;
}

