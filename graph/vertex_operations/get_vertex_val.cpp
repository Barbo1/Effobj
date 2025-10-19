#include "../../graph.hpp"

float Graph::get_vertex_val (uint32_t index) {
  if (this->vertex_values.size() <= index) return 0.f;
  else return this->vertex_values[index];
}
