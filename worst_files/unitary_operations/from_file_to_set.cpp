#include "../../worst.hpp"
#include <fstream>

WordSet from_file_to_set(const std::string & path){
  WordSet ws = WordSet();
  std::ifstream file(path);

  if (file.is_open()) {
    file.seekg(0, std::ios_base::end);
    int len = file.tellg();
    char * text = new char[len];
    file.seekg(0, std::ios_base::beg);
    file.read(text, len);

    std::string word = "";
    for (int i = 0, lett = text[0]; i < len; i++, lett = text[i]) {
      if (lett != ' ' && lett != '\n') [[likely]] {
        word += lett;
      } else [[unlikely]] {
        if (word.length() > 0) {
          ws.aggregate_word(word);
        }
        word = "";
      }
    }
    delete [] text;
    file.close();
  }
  return ws;
}

