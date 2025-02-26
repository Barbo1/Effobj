#include "../../xpres.hpp"

bool Xpres::compare_tree_equal (nodeEX root1, nodeEX root2, bool not_same_level) noexcept {
  if (root1 == nullptr || root2 == nullptr) { return root1 == nullptr && root2 == nullptr; }
  if (root1->type != root2->type || root1->id != root2->id) { return false; }
  if (root1->type == 'p' && is_oper_bm (root1->id)) {

    /* Get the sons of both trees. */
    nodeEX res;
    std::vector<nodeEX> arr1 = get_array_sons (root1);
    std::vector<nodeEX> arr2 = get_array_sons (root2);
    uint64_t len1 = arr1.size();
    if (len1 == 0 || len1 != arr2.size()) { 
      return false; 
    }

    /* Match pairs of nodes that represent equal subexpresions (they can be in a no straight order). */
    uint64_t j;
    for (uint64_t i = 0; i < len1; i++) {
      j = i;
      while (j < len1 && !compare_tree_equal(arr1[i], arr2[j])) j++;
      if (j == len1) return false;
      std::swap(arr2[i], arr2[j]);
    }

    return not_same_level || compare_tree_equal(root1->sibling, root2->sibling);

  } else {
    return compare_tree_equal (root1->son, root2->son) && 
      (not_same_level || compare_tree_equal (root1->sibling, root2->sibling));
  }
}
