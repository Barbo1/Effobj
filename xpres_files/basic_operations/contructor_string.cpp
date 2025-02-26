#include "../../xpres.hpp"

Xpres::Xpres(std::string_view sexp) {
  char let;
  int j, curr, i, n, last;
  bool is_number, is_hash, has_dot;
  nodeEX res_1;
  nodeEX res_2;
  std::string operand;
  std::vector<std::string> token_names;

  /* (1) */
  int top = 1;
  for (i = 0; i < sexp.size(); i++) {
    if (sexp[i] == '(') {
      top++;
    }
  }

  std::string * ret = new std::string[top] {""};
  unsigned * prev = new unsigned[top] {0};

  is_number = true;
  curr = 0;
  last = 0;
  j = 0;

  /* (2) */
  for (i = 0; i < sexp.size(); i++) {
    let = sexp[i];
    if (let != ' ') {
      if (let == '(') {
        ret[curr] += (is_number ? '#' : '$') + std::to_string(last+1);
        prev[++j] = curr;
        curr = ++last;
        is_number = true;
      } else if (let == ')') {
        curr = prev[j--];
        is_number = false;
      } else {
        is_number = !is_character(let); 
        ret[curr] += let;
      }
    }
  }

  nodeEX * fin = new nodeEX[top] {nullptr};

  for (curr = top-1; curr >= 0; curr--) {
    char res;
    std::string current_str = ret[curr];
    std::stack<nodeEX> st_tok;
    std::stack<char> st_ope;

    i = 0;
    is_number = false;
    n = current_str.size();

    while (i < n) {
      operand = "";
      is_hash = false;
      let = current_str[i];
      if (let == '#') {
        is_hash = true;
        std::string res_str = "";
        let = current_str[++i];
        while (std::isdigit(let)) {
          res_str += let;
          let = current_str[++i];
        }
        operand = "#";
        st_tok.push(fin[atoi(res_str.c_str())]);
      } else if (is_character(let)) {
        is_number = is_digit(let);
        has_dot = let == '.';
        while (is_character(let)) {
          has_dot |= let == '.';
          operand += let;
          let = current_str[++i];
        }
        if (is_number) {
          if (has_dot) {
            st_tok.push(create_node('d', std::bit_cast<data_t>(atof(operand.c_str()))));
          } else { 
            st_tok.push(create_node('i', atoi(operand.c_str())));
          }
        } else if (let == '$') {
          std::string res_str = "";
          let = current_str[++i];
          while(std::isdigit(let)) {
            res_str += let;
            let = current_str[++i];
          }

          // for now, it is assumed that the function is one of the recognized.
          st_tok.push(create_node(
                'f', 
                exists<std::string_view>(operand, recognized_functions),
                fin[atoi(res_str.c_str())],
                nullptr
                ));
          continue;
        } else {
          j = exists(operand, token_names);
          if (j == -1) {
            j = token_names.size();
            token_names.push_back(operand);
          }
          st_tok.push(create_node('t', j));
        }
      }
      if (let != '\0') {
        while (!st_ope.empty() && (((res = st_ope.top()) == '-' && let == '-') || 
              (precedence(res, let) > 0 && 
               !(res == '@' && let == '~' || 
                 res == '!' && let == '~' || 
                 res == '!' && let == '-' && operand == "" || 
                 res == '@' && let == '-' && operand == "") 
              ))) {
          st_ope.pop();
          res_1 = st_tok.top();
          st_tok.pop();
          if (res == '!' || res == '~' || res == '@') {
            st_tok.push(create_node('p', res == '@' ? '-' : res, res_1, nullptr)); 
          } else {
            res_2 = st_tok.top();
            st_tok.pop();
            st_tok.push(deduce_operation_binary(res_2, res_1, res));
          }
        }
        st_ope.push(operand == "" && let == '-' ? '@' : let);
      } 
      i++;
    }

    // consume the stacks.
    while (!st_ope.empty()) {
      res = st_ope.top();
      st_ope.pop();
      res_1 = st_tok.top();
      st_tok.pop();
      if (res == '!' || res == '~' || res == '@') {
        st_tok.push(create_node('p', res == '@' ? '-' : res, res_1, nullptr)); 
      } else {
        res_2 = st_tok.top();
        st_tok.pop();
        st_tok.push(deduce_operation_binary(res_2, res_1, res));
      }
    }
    fin[curr] = st_tok.top();
  }

  this->root = fin[0];

  /* (3) */
  for (auto it = token_names.begin(); it != token_names.end(); it++) {
    this->token_info.push_back({*it, '\0', nullptr});
  }

  delete [] ret;
  delete [] prev;
  delete [] fin;
}
