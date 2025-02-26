#include "../../xpres.hpp"

template<typename T>
bool Xpres::set_value(std::string_view name, const T& value) {
  auto it = this->token_info.begin();
  while (it != this->token_info.end() && std::get<0>(*it) != name) {
    it++;
  }
  if (it != this->token_info.end()) {
    auto& [_, type, data] = *it;
    switch (type) {
      case 'E':
        delete (Matrix<Xpres> *)data;
        break;
      case 'M':
        delete (Matrix<double> *)data;
        break;
      case 'm':
        delete (Matrix<int64_t> *)data;
        break;
      case 'e':
        delete (Xpres *)data;
        break;
      case 'd':
        delete (double *)data;
        break;
      case 'i':
        delete (int64_t *)data;
        break;
      default:
        break;
    }
    type = '\0';
    if (std::is_same_v<Matrix<Xpres>, T>) {
      type = 'E';
    } else if (std::is_same_v<Matrix<double>, T>) {
      type = 'M';
    } else if (std::is_same_v<Matrix<int64_t>, T>) {
      type = 'm';
    } else if (std::is_same_v<Xpres, T>) {
      type = 'e';
    } else if (std::is_same_v<double, T>) {
      type = 'd';
    } else if (std::is_same_v<int64_t, T>) {
      type = 'i';
    } else {
      return false;
    }
    data = (void *) (new T(value));
    return true;
  }
  return false;
}

std::vector< std::tuple< std::string, char, void*> > Xpres::get_tokens () {
  return this->token_info;
}
