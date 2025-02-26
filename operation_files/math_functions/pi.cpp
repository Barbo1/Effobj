#include "../../operation.hpp"

double pi (unsigned precition) {
  int n;
  double or_2;
  int or_1 = 1; 
  int cinco_pot = 5; 
  int dos_pot = 239;
  int menos_1 = 4;
  double var_1 = (double)4/5; 
  double var_2 = (double)4/239;
  for (n = 1; n < precition; n++) {
    or_1 += 2;
    menos_1 *= -1;
    cinco_pot *= 25;
    dos_pot *= 57121;
    or_2 = (double)menos_1/or_1;
    var_1 += (double)or_2/cinco_pot;
    var_2 += (double)or_2/dos_pot;
  }
  return 4*var_1 - var_2;
}
