#include "../../../xpres.hpp"

bool Xpres::is_oper_b (uint8_t op) { 
  return exists((char)op, binary_nomulti_operators) != -1; 
}
