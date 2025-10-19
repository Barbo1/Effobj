#include "../../graph.hpp"
#include <cstdint>

bool Graph::create_edge (uint32_t index1, uint32_t index2) {
  if (index1 < this->vertex_values.size() && index2 < this->vertex_values.size())
    return false;
  
  uint32_t num = this->primes[index1] * this->primes[index2];
  if (find_node_AVL(this->edges, num) != nullptr)
    return false;

  insert_node_AVL (num, {index1, index2, 1.f}, this->edges);
  this->edge_many++;
  return true;
}
