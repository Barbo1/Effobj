#include "../../graph.hpp"

bool Graph::create_edge (uint32_t index1, uint32_t index2) {
  if (index1 < this->primes.size() && index2 < this->primes.size())
    return false;
  this->edges.add_node(this->primes[index1] * this->primes[index2], 0.f);
  return true;
}
