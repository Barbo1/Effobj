#include "../../worst.hpp"
#include <utility>

/* 
 97 <= (*pt & 0x20) && (*pt & 0x20) <= 122 
*/
#define PERMITED_CHAR(pt) ((65 <= *pt && *pt <= 90) || (97 <= *pt && *pt <= 122))

unsigned WordSet::aggregate_word(std::string_view word){
  char * com = new char[MAX_LEN_WORD], * str = com, * fin, * i;
  nodeWS tr, tr_prev, tr_father;
  int n = word.length();

  if (n <= MAX_LEN_WORD) {
    word.copy(str, n);
    fin = str+n-1;
    while (fin != str && !PERMITED_CHAR(fin)) fin--;
    while (fin != str && !PERMITED_CHAR(str)) str++;

    /* enter if the there is to letters in distincts positions. */
    if (fin != str || PERMITED_CHAR(str)) {
      fin++;
      i = str;
      while (i < fin && (PERMITED_CHAR(i) || *i == 39)) {
        *(i++) |= 32;
      }

      /* enter if the symbols of the word are letters or '. */
      if (i == fin) {
        tr = this->root->son;
        tr_father = this->root;
        tr_prev = nullptr;
        while (tr != nullptr && str < fin && tr->letter <= *str) {
          if (tr->letter != *str) {
            tr_prev = std::exchange(tr, tr->sibling);
          } else {
            tr_father = std::exchange(tr, tr->son);
            tr_prev = nullptr;
            str++;
          }
        }

        /* enter if the word were not found. */
        if (!tr_father->finished || str < fin) {
          if (tr_father->finished) {
            if (tr_prev == nullptr) {
              if (tr != nullptr && tr->letter > *str) {
                tr_father = 
                  tr_father->son = 
                    tr = create_node (
                        *(str++), 
                        false, 
                        nullptr, 
                        std::exchange (tr_prev, tr)
                      );
              }
            } else {
              if (tr == nullptr || tr->letter > *str) {
                tr_father = 
                  tr = create_node (
                      *(str++), 
                      false, 
                      nullptr, 
                      std::exchange(tr_prev->sibling, tr)
                    );
              }
            }
          }
          for (; str < fin; str++) {
            tr_father = 
              tr = create_node (*str, false, nullptr, std::exchange(tr_father->son, tr));
          }
          tr_father->finished = true;
          delete [] com;
          return 0;
        }
      }
    }   
  }
  delete [] com;
  return 1;
}
