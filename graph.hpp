#pragma once

#include "./tree.hpp"
#include <cstdint>
#include <vector>
#include <memory>

/* This class implements undirected graphs. It uses AVL trees to store the edges with its values,
 * is operations like searching are guaranteed to be made in log(v). Given e as the number of
 * edges ans v the number of vertex, the order of memory used is O(v + e). The order time of the
 * operations are:
 *  - graph creation -> O(v * log(v)) [i suppose, but technically i must count also e * log(e)]
 *  - create_edge -> O(log(e))
 *  - remove_edge -> O(log(e))
 *  - edge_number -> O(1)
 *  - set_vertex_val -> O(1)
 *  - get_vertex_val -> O(1)
 *  - get_edge_val -> O(log(e))
 *  - set_edge_val -> O(log(e))
 *  - neighbors -> O(v * log(e))
 *  - adjacents -> O(log(e))
 *
 *  Creation probably take O(v) operations, but deletion of a vertex is something particularly 
 *  inconsistent with the representation, in which is have edges from 1 to n exactly. The deletion
 *  will make sense if i change the [1 ... n] to [1...(i-1) (i+1)...n], changing [(i+1)...n] to
 *  [i...(n-1)]. This operation will take O(v * log(e) + e) apparently.
 * */

class Graph {
  private:
    struct _edges_types {
      uint32_t n1;
      uint32_t n2;
      float value;
    };

    uint32_t edge_many;
    uint32_t primes_many;
    nodeAVL<_edges_types> edges;
    std::shared_ptr<int32_t[]> primes;
    std::vector<float> vertex_values;

  public:
    Graph (uint32_t);
    Graph (const Graph &);
    Graph (Graph &&);
    Graph& operator= (const Graph &);
    Graph& operator= (Graph &&);

    bool create_edge (uint32_t, uint32_t);
    bool remove_edge (uint32_t, uint32_t);
    bool is_edge (uint32_t, uint32_t);
    uint32_t edge_number ();
    uint32_t vertex_number ();

    void set_vertex_val (uint32_t, float);
    float get_vertex_val (uint32_t);
    float get_edge_val (uint32_t, uint32_t);
    void set_edge_val (uint32_t, uint32_t, float);

    std::vector<uint32_t> neighbors (uint32_t);
    bool adjacents (uint32_t, uint32_t);

    /* Not yet implemented. */

    std::vector<uint32_t> shortest_path (uint32_t, uint32_t);
    bool is_flow_net ();
    Graph find_min_flow ();
    Graph power (int);
};
