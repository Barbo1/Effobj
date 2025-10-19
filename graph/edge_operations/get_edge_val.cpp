#include "../../graph.hpp"

float Graph::get_edge_val (uint32_t index1, uint32_t index2) {
  nodeAVL<_edges_types> nd = find_node_AVL(
    this->edges, this->primes[index1] * this->primes[index2]
  );
  if (nd == nullptr) return 0.f;
  return nd->value.value;
}
