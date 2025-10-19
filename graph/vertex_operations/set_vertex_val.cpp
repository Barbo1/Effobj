#include "../../graph.hpp"

void Graph::set_vertex_val (uint32_t index, float value) {
  if (index < this->primes_many) {
    this->vertex_values[index] = value;
  }
}
