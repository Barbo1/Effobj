#include "../../graph.hpp"

bool Graph::is_edge (uint32_t index1, uint32_t index2) {
  nodeAVL<_edges_types> nd = find_node_AVL(
    this->edges, this->primes[index1] * this->primes[index2]
  );
  return nd != nullptr;
}
