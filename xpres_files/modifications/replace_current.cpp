#include "../../xpres.hpp"

Xpres::iterator& Xpres::iterator::replace_current(const Xpres & exp) {
  const uint64_t n = this->token_info.size();
  const nodeEX root = get_root(this->points);

  bool * tokens_bool = repetition_counter_arr(root, this->points.top(), n);

  uint64_t i = 0;
  uint64_t j;
  uint64_t new_id = n;
  std::vector<uint64_t> arr;
  std::string str;

  arr.reserve(exp.token_info.size());
  for (i = 0; i < exp.token_info.size(); i++) {
    str = std::get<0>(exp.token_info[i]);
    j = 0;
    while (j < n && str != std::get<0>(this->token_info[j])) {
      j++;
    }

    auto res = copy_pair (
        std::pair<char, void*> (
          std::get<1>(exp.token_info[i]), 
          std::get<2>(exp.token_info[i])
        )
      );
    if (j != n) {
      if (tokens_bool[j]) {
        arr.push_back (new_id++);
        this->token_info.push_back (
            std::make_tuple (
              this->expresion.get_new_name(str), 
              res.first, 
              res.second
            )
          );
      } else {
        arr.push_back(j);
        free_pair (
            std::pair<char, void*> (
              std::get<1>(this->token_info[j]), 
              std::get<2>(this->token_info[j])
            )
          );
        this->token_info[j] = std::make_tuple(str, res.first, res.second);
      }
    } else {
      arr.push_back(new_id++);
      this->token_info.push_back(std::make_tuple(str, res.first, res.second));
    }
  }

  nodeEX copia = recalculate_ids(copy_nodes(exp.root), &arr[0]);
  nodeEX res = this->points.top();

  this->points.pop();
  if (!this->points.empty()) {
    nodeEX father = this->points.top();
    copia->sibling = res->sibling;
    if (father->son == res) {
      father->son = copia;
    } else {
      father = father->son;
      while (father->sibling != res) {
        father = father->sibling;
      }
      father->sibling = copia;
    }
    res->sibling = nullptr;
  }
  this->points.push(copia);
  delete_nodes(res);

  arr.clear();
  arr.reserve(new_id);
  j = 0;
  for (i = 0; i < n; i++) {
    if (tokens_bool[i] || !tokens_bool[n + i]) {
      if (j < i) { 
        this->token_info[j] = this->token_info[i]; 
      }
      arr.push_back(j);
      j++;
    } else {
      arr.push_back(0);
    }
  }
  for (; i < new_id; i++, j++) {
    this->token_info[j] = this->token_info[i];
    arr.push_back(j);
  }
  for (; new_id > n; new_id--) {
    this->token_info.pop_back();
  }

  recalculate_ids(root, &arr[0]);

  delete [] tokens_bool;
  return *this;
}
