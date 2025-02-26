#include "../../../xpres.hpp"

bool Xpres::is_oper_bm (uint8_t op) { 
  return exists((char)op, binary_multi_operators) != -1; 
}
