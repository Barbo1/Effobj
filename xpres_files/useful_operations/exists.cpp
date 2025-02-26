#include "../../xpres.hpp"

template<typename T>
int Xpres::exists(T var, const std::vector<T> & vec) {
  uint64_t i = 0;
  uint64_t n = vec.size();
  while (i < n && vec[i] != var) { 
    i++; 
  }
  if (i == n) { 
    return -1; 
  } else { 
    return i; 
  }
}

template<typename T, std::size_t N>
int Xpres::exists(T var, const std::array<T, N> & arr) {
  uint64_t i = 0;
  uint64_t n = N;
  while (i < n && arr[i] != var) { 
    i++; 
  }
  if (i == n) { 
    return -1; 
  } else { 
    return i; 
  }
}
