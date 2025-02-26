#include "../../xpres.hpp"

std::ostream& operator<<(std::ostream & ofile, const Xpres & exp) {
  ofile << exp.to_string();

  /*ofile << print_aux_1(exp.root, exp.root->son) << std::endl;*/
  return ofile;
}
