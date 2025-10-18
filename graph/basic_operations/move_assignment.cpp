#include "../../graph.hpp"
#include <cstdint>
#include <utility>

Graph& Graph::operator=(Graph && g) {
  this->vertex_values = std::exchange(g.vertex_values, std::vector<float>());
  this->primes = std::exchange(g.primes, std::vector<int32_t>());
  this->edges = std::exchange(g.edges, AVLTree());
  return *this;
}
