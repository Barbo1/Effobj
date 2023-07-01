#include <vector>

class NodeSet;

class Graph {
public:
    Graph(unsigned);
    Graph(const Graph &);
    Graph(Graph &&);
    Graph operator=(const Graph &);
    Graph operator=(Graph &&);
    virtual ~Graph(){};

    virtual int create_edge(unsigned, unsigned) = 0;
    virtual int remove_edge(unsigned, unsigned) = 0;
    virtual bool adjacent(unsigned, unsigned) = 0;
    virtual NodeSet neighbors(unsigned) = 0;
    virtual void set_vertex_val(unsigned, double) = 0;
    virtual void set_edge_val(unsigned, unsigned, double) = 0;
    virtual double get_vertex_val(unsigned) = 0;
    virtual double get_edge_val(unsigned, unsigned) = 0;

    virtual NodeSet shortest_path(unsigned, unsigned) = 0;
};

class __Graph_Directed__ : public Graph {
    __Graph_Directed__ find_topology(); 
};

class __Graph_Undirected__ : public Graph {
    bool is_flow_net();
    Graph find_min_flow();
};
