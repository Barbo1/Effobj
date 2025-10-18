#include "../../graph.hpp"

Graph::Graph(const Graph & g) {
  this->vertex_values = g.vertex_values;
  this->primes = g.primes;
  this->edges = g.edges;
}
