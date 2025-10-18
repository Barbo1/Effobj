#include "../../graph.hpp"

bool Graph::is_edge (uint32_t index1, uint32_t index2) {
  return this->edges.find (this->primes[index1] * this->primes[index2]);
}
