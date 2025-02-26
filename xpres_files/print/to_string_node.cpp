#include "../../xpres.hpp"

// esta funcion puede ser eliminada.
static std::string print_aux_1(
        nodeEX father, 
        nodeEX first_son, 
        std::string sss = "-", 
        bool no_first = true) {
    std::string ret = "";
    data_t val;
    
    ret += sss + " ";
    if (father->type == 'd') {
        ret += std::to_string(* (double*) &(val = father->id));
    } else if (father->type == 'p') {
        ret += (char)father->id;
    } else {
        ret += std::to_string(father->id);
    }
    ret += " ";
    ret += father->type;
    ret += "\n";
    
    while (first_son != nullptr) {
        ret += print_aux_1(first_son, first_son->son, sss+"-");
        first_son = first_son->sibling;
    }
    return ret;
}

/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/

std::string Xpres::to_string_aux (
    nodeEX father, 
    nodeEX first_son, 
    const std::vector<std::tuple<std::string, char, void*>> & token_info, 
    bool no_first) noexcept {
  std::string ret = "";
  data_t val;

  if (father->type == 'd') {
    ret += std::to_string(* (double*) &(val = father->id));
  } else if (father->type == 'i') {
    ret += std::to_string(father->id);
  } else if (father->type == 't') {
    ret += std::get<0>(token_info[father->id]);
  } else if (father->type == 'p') {
    if (father->id == '+') {
      while (first_son != nullptr) {
        if (first_son->type == 'p' && precedence('+', first_son->id) > 0) {
          if (no_first) {
            ret += '(';
          }
          ret += to_string_aux(first_son, first_son->son, token_info);
          ret += ')';
        } else {
          if (first_son->type == 'p' && first_son->id == '-') {
            ret += " - ";
          } else if (no_first) {
            ret += " + ";
          }
          ret += to_string_aux(first_son, first_son->son, token_info);
        }
        first_son = first_son->sibling;
        no_first = true;
      }
    } else { 
      bool resol = is_oper_u ((char)father->id);
      while (first_son != nullptr) {
        if (no_first || resol) {
          if (!resol) {
            ret += " ";
          }
          ret += father->id;
          if (!resol) {
            ret += " ";
          }
        }
        if (first_son->type == 'p' && precedence(father->id, first_son->id) > 0) {
          ret += '(';
          ret += to_string_aux(first_son, first_son->son, token_info);
          ret += ')';
        } else {  
          ret += to_string_aux(first_son, first_son->son, token_info);
        }
        first_son = first_son->sibling;
        no_first = true;
      }
    }
  } else if (father->type == 'f') {
    ret += recognized_functions[father->id];
    ret += '(';
    ret += to_string_aux(first_son, first_son->son, token_info);
    ret += ')'; 
  }

  return ret;
}

std::string Xpres::to_string_node (
    nodeEX root, 
    const std::vector<std::tuple<std::string, char, void*>> & token_info
    ) noexcept {
  std::string str = to_string_aux(root, root->son, token_info);

  // this code below is something fucking disgusting, but it works. The thing is that
  // the expresion dont will be well printed if I dont do it. I will change this (it 
  // will took time).
  if (str.size() > 1) {
    unsigned i = 0;
    unsigned n = str.size()-2;
    while (i < n) {
      if (str[i] == '-' && str[i+1] == ' ' && str[i+2] == '-' ) {
        str.erase(i+2,1);
        n = str.size()-2;
      } else {
        i++;
      }
    }
  }

  return str;
}
