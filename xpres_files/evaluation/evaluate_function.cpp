#include "../../xpres.hpp"

std::pair<char, void*> Xpres::evaluate_function(std::pair<char, void*> op1, std::string_view fun) {
  double a = 0;

  /* is not posible to evaluate matrices or expresion with functions. */
  switch (op1.first) {
    case 'i':
      if (fun == "cos") {
        a = cos(* (data_t *) op1.second);
      } else if (fun == "cosh") {
        a = cosh(* (data_t *) op1.second);
      } else if (fun == "acos") {
        a = acos(* (data_t *) op1.second);
      } else if (fun == "sin") {
        a = sin(* (data_t *) op1.second);
      } else if (fun == "sinh") {
        a = sinh(* (data_t *) op1.second);
      } else if (fun == "asin") {
        a = asin(* (data_t *) op1.second);
      } else if (fun == "tan") {
        a = tan(* (data_t *) op1.second);
      } else if (fun == "tanh") {
        a = tanh(* (data_t *) op1.second);
      } else if (fun == "atan") {
        a = atan(* (data_t *) op1.second);
      } else if (fun == "exp") {
        a = exp(* (data_t *) op1.second);
      } else if (fun == "log") {
        a = log(* (data_t *) op1.second);
      } else {
        a = 0;
      }
      break;
    case 'd':
      if (fun == "cos") {
        a = cos(* (double *) op1.second);
      } else if (fun == "cosh") {
        a = cosh(* (double *) op1.second);
      } else if (fun == "acos") {
        a = acos(* (double *) op1.second);
      } else if (fun == "sin") {
        a = sin(* (double *) op1.second);
      } else if (fun == "sinh") {
        a = sinh(* (double *) op1.second);
      } else if (fun == "asin") {
        a = asin(* (double *) op1.second);
      } else if (fun == "tan") {
        a = tan(* (double *) op1.second);
      } else if (fun == "tanh") {
        a = tanh(* (double *) op1.second);
      } else if (fun == "atan") {
        a = atan(* (double *) op1.second);
      } else if (fun == "exp") {
        a = exp(* (double *) op1.second);
      } else if (fun == "log") {
        a = log(* (double *) op1.second);
      } else {
        a = 0;
      }
      break;
    default: 
      return {'\0', (void*)nullptr};
  }

  /* Depending on the funtion, get the double and put it in the op1. */

  if (op1.first == 'i') {
    op1.first = 'd';
  }
  double * b = (double*)op1.second;
  *b = a;

  return op1;
}
