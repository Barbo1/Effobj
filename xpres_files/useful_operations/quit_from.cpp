#include "../../xpres.hpp"

template<typename T>
void Xpres::quit_from(T var, const std::vector<T> & vec) {
  auto it = vec.begin();
  while (it != vec.end() && *it != var) {
    it++;
  }
  if (it != vec.end()) {
    vec.erase(it);
  }
} 
