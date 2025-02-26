#include "../../worst.hpp"

WordSet::~WordSet(){
  delete_nodes(this->root);
}
