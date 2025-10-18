#include "../../graph.hpp"

float Graph::get_edge_val (uint32_t index1, uint32_t index2) {
  return this->edges.get_value(this->primes[index1] * this->primes[index2]);
}
