#include "../../graph.hpp"
#include "../../operation.hpp"
#include <memory>

Graph::Graph (unsigned many) {
  this->vertex_values = std::vector<float> (many, 1.f);
  this->primes = primes_by_many_static (many);
  this->primes_many = many;
  this->edges = nullptr;
  this->edge_many = 0;
}
