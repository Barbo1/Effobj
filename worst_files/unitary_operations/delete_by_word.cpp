#include "../../worst.hpp"
#include <utility>

unsigned WordSet::delete_word(const std::string & word) {
  char * com = new char[MAX_LEN_WORD];
  char * str = com, * fin;
  int n = word.length(), i = -1, ret = 1;
  nodeWS * data = new nodeWS[MAX_LEN_WORD];
  nodeWS tr_father = this->root;
  nodeWS tr = tr_father->son;

  if (n <= MAX_LEN_WORD) {
    word.copy(com, n);
    fin = str+n;

    /* search a word to delete.
     * */
    while (tr != nullptr && str < fin) {
      if (tr->letter == *str) [[unlikely]] { 
        data[i++] = tr_father;
        tr_father = std::exchange(tr, tr->son);
        str++;
      } else [[likely]] {
        tr = tr->sibling;
      }
    }

    /* delete the finded word.
     * */
    if (tr_father->finished && str == fin) {
      tr_father->finished = false;
      tr = std::exchange (tr_father, data[i--]);
      while (
          i != -1 && 
          !tr->finished && 
          tr->son == nullptr && 
          tr->sibling == nullptr && 
          tr_father->son == tr
          ) {
        tr_father->son = nullptr;
        delete tr;
        tr = std::exchange(tr_father, data[i--]);
      }
      if (tr->son == nullptr && !tr->finished) {
        if (tr_father->son == tr) [[unlikely]] {
          tr_father->son = tr->sibling;
        } else [[likely]] {
          tr_father = tr_father->son;
          while (tr_father->sibling != tr) {
            tr_father = tr_father->sibling;
          }
          tr_father->sibling = tr->sibling;
        }
        delete tr;
      }
      ret = 0;
    }
  }
  return ret;
}
