#ifndef __Graph_mod
#define __Graph_mod

#include "./needed.hpp"
#include <vector>

typedef struct _node_avl * nodeAVL;

template <typename T>
class Graph {
protected:
    std::vector<T> _data_;
    std::vector<nodeAVL> _adjacency_;
public:
    Graph ();
    Graph (index);
    Graph (const Graph &);
    Graph (Graph &&);
    Graph & operator= (const Graph &) = 0;
    Graph & operator= (Graph &&) = 0;
    bool operator== (const Graph &) = 0;
    virtual ~Graph (){};

    virtual void create_edge () = 0;
    virtual void remove_edge (index, index) = 0;
    virtual index edge_quan () = 0;
    virtual bool adjacents (index, index) = 0;
    virtual std::vector<index> neighbors (index) = 0;
    virtual void set_vertex_val (index, T) = 0;
    virtual void set_edge_val (index, index, T) = 0;
    virtual T get_vertex_val (index) = 0;
    virtual T get_edge_val (index, index) = 0;

    virtual std::vector<index> shortest_path (index, index) = 0;
    virtual Graph complement () = 0; 
};

template <typename T>
class GraphDirected : public Graph<T> {
public:
    GraphDirected find_topology (); 
    GraphDirected trasnpose (); 
};

template <typename T>
class GraphUndirected : public Graph<T> {
public:
    bool is_flow_net ();
    GraphUndirected find_min_flow ();
    GraphUndirected power (int);
};

 #endif
