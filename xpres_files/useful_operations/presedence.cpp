#include "../../xpres.hpp"

int Xpres::precedence (char op1, char op2) {
  uint64_t i = 0, j = 0;
  while (operators[i++] != op1);
  while (operators[j++] != op2);
  return (i > j) - (i < j);
}
