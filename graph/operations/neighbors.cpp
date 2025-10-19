#include "../../graph.hpp"
#include <cstdint>

std::vector<uint32_t> Graph::neighbors (uint32_t index1) {
  std::vector<uint32_t> ret = std::vector<uint32_t>();
  if (this->vertex_values.size() < index1) 
    return ret;
  uint32_t prim = this->primes[index1];
  for (uint32_t i = 0; i < index1; i++)
    if (find_node_AVL (this->edges, this->primes[i] * prim))
      ret.push_back (i);
  for (uint32_t i = index1 + 1; i < this->primes_many; i++)
    if (find_node_AVL (this->edges, this->primes[i] * prim))
      ret.push_back (i);
  return ret;
}
