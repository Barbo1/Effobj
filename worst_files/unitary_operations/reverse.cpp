#include "../../worst.hpp"

WordSet WordSet::operator!() const {
  std::string str;
  WordSet ws;
  for (WordSet::iterator it = WordSet::iterator(*this); !it.is_finished(); ++it) {
    str = *it;
    for (int lf = str.length(), ls = 0; ls < lf; ls++, lf++) {
      std::swap(str[ls], str[lf]);
    }

    ws.aggregate_word(str);
  }
  return ws;
}
