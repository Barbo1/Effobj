#include "../../../xpres.hpp"

bool Xpres::is_oper_u (uint8_t op) { 
  return exists((char)op, unitary_operators) != -1; 
}
