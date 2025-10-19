#include "../../graph.hpp"

bool Graph::adjacents (uint32_t index1, uint32_t index2) {
  if (index1 < this->vertex_values.size() && index2 < this->vertex_values.size())
    return false;

  return find_node_AVL (
    this->edges, this->primes[index1] * this->primes[index2]
  ) != nullptr;
}


