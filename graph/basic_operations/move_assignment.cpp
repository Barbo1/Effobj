#include "../../graph.hpp"
#include <utility>

Graph& Graph::operator=(Graph && g) {
  this->vertex_values = std::exchange(g.vertex_values, std::vector<float>());
  this->primes_many = std::exchange(g.primes_many, 0);
  this->edge_many = std::exchange(g.edge_many, 0);
  this->primes = std::exchange(g.primes, nullptr);
  this->edges = std::exchange(g.edges, nullptr);
  return *this;
}
