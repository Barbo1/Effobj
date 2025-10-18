#pragma once

#include "./tree.hpp"
#include <cstdint>
#include <vector>

/* This class implements undirected graphs. It uses AVL trees to store the edges with its values,
 * is operations like searching are guaranteed to be made in log(v). Given e as the number of
 * edges ans v the number of vertex, the order of memory used is O(v + e). The order time of the
 * operations are:
 *  - graph creation -> O(v * log(v) + e * log(e)) [i suppose]
 *  - create_edge -> O(log(e)).
 *  - remove_edge -> O(log(e)).
 *  - edge_number -> O(1).
 *  - set_vertex_val -> O(1).
 *  - get_vertex_val -> O(1).
 *  - get_edge_val -> O(log(e)).
 *  - set_edge_val -> O(log(e)).
 *  - neighbors -> O(v * log(e)).
 *  - adjacents -> O(log(e)).
 * */

class Graph {
  protected:
    std::vector<int32_t> primes;
    std::vector<float> vertex_values;
    AVLTree edges;

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
