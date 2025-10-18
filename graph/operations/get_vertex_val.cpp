#include "../../graph.hpp"

float Graph::get_vertex_val (uint32_t index) {
  if (this->primes.size() <= index) return 0;
  else return this->vertex_values[index];
}
