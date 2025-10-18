#include "../../graph.hpp"

Graph& Graph::operator=(const Graph & g) {
  this->vertex_values = g.vertex_values;
  this->primes = g.primes;
  this->edges = g.edges;
  return *this;
}
