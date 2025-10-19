#include "../../graph.hpp"

Graph& Graph::operator=(const Graph & g) {
  this->vertex_values = g.vertex_values;
  this->primes = g.primes;
  this->primes_many = g.primes_many;
  this->edges = copy_tree_AVL (g.edges);
  this->edge_many = g.edge_many;
  return *this;
}
