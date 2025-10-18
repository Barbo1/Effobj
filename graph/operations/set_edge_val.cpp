#include "../../graph.hpp"

void Graph::set_edge_val (uint32_t index1, uint32_t index2, float value) {
  this->edges.set_value(this->primes[index1] * this->primes[index2], value);
}
