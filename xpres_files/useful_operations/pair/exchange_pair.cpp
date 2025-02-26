#include "../../../xpres.hpp"

void Xpres::exchange_pair (std::pair<char, void*> op1, std::pair<char, void*> op2) {
  char a = op1.first;
  op1.first = op2.first;
  op2.first = a;

  void * b = op1.second;
  op1.second = op2.second;
  op2.second = b;
}
