#include "../../xpres.hpp"

std::ostream & operator<<(std::ostream & ofile, const Xpres::iterator & it) {
  ofile << Xpres::to_string_node (it.points.top(), it.token_info);

  /*ofile << print_aux_1(exp.root, exp.root->son) << std::endl;*/
  return ofile;
}
