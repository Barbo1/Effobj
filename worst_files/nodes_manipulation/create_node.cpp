#include "../../worst.hpp"

[[nodiscard("Discarding node creation")]] nodeWS WordSet::create_node (
    char letter, 
    bool finished, 
    nodeWS son, 
    nodeWS sibling
    ) {
  nodeWS node_new = new node_word_set_struct;
  node_new->letter = letter;
  node_new->finished = finished;
  node_new->sibling = sibling;
  node_new->son = son;
  return node_new;
}
