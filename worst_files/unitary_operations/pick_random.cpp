#include "../../worst.hpp"
#include <utility>
#include <ctime>

std::vector<std::string> WordSet::pick_random (unsigned cant_words) {
  std::vector<std::string> vt;
  std::vector<std::string>::iterator it;
  std::string str;
  nodeWS res;
  nodeWS * node_arr = new nodeWS[LETTER_QUAN];
  nodeWS * node_word = new nodeWS[MAX_LEN_WORD];
  int n, i, cant_;

  srand ((unsigned)clock());
  while (cant_words > 0) {
    i = cant_ = 0;
    res = this->root->son;

    /* pick a random branch of the tree. */
    while (res != nullptr) {
      /* pick all the childs. */
      n = 0;
      while (res != nullptr) {
        node_arr[n++] = std::exchange(res, res->sibling);
      }

      /* store one of the child randomly */
      res = node_arr[rand() % n];
      node_word[i++] = res;
      cant_ += res->finished;
      res = res->son;
    }

    /* pick a random word of the selected branch. */
    cant_ = (rand() % cant_) + 1;
    i = 0;
    str = "";
    while (cant_ > 0) {
      str += node_word[i]->letter; 
      if (node_word[i++]->finished) cant_--;
    }

    /* delete the selected word and store it*/
    vt.push_back(str);
    this->delete_word(str);
    cant_words--;
  }
  for (const auto& str: vt) {
    this->aggregate_word(str);
  }
  delete [] node_arr;
  delete [] node_word; 
  return vt;
}
