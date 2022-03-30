// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int priority(char op) {
  switch (op) {
  case '(':
    return 0;
    break;
  case ')':
    return 1;
    break;
  case '+':case'-':
    return 2;
    break;
  case '*':case'/':
    return 3;
    break;
  default:
    return 4;
    break;
  }
}
int prior_calc(char value) {
  switch (value) {
  case '+':
    return 1;
    break;
  case '-':
    return 2;
    break;
  case '*':
    return 3;
    break;
  case '/':
    return 4;
    break;
  case ' ':
    return 0;
    break;
  default:
    return 5;
    break;
  }
}
std::string infx2pstfx(std::string inf) {
  std::string pref;
  TStack<int, 100> stack;
  for (int i = 0; i < inf.length(); i++) {
    if (priority(inf[i]) == 4) {
      pref.push_back(inf[i]);
      pref.push_back(' ');
    }  else {
         if (priority(inf[i]) == 0) {
            stack.push(inf[i]);
         } else if (priority(inf[i]) > priority(stack.get())) {
             stack.push(inf[i]);
           }  else if (stack.isEmpty()) {
                stack.push(inf[i]);
             } else if (priority(inf[i]) == 1) {
               while (priority(stack.get()) != 0) {
                 pref.push_back(stack.get());
                 pref.push_back(' ');
                 stack.pop();
               }
               stack.pop();
             }  else if (priority(inf[i]) <= priority(stack.get())) {
                  if (priority(stack.get()) > 1) {
                    pref.push_back(stack.get());
                    pref.push_back(' ');
                    stack.pop();
                  }
                  stack.push(inf[i]);
                }
       }
  }
  while (!stack.isEmpty()) {
    pref.push_back(stack.get());
    pref.push_back(' ');
    stack.pop();
  }
  pref.pop_back();
  return pref;
}

int eval(std::string pref) {
  TStack<int, 100> stack_p;
  int otvet = 0;
  std::string otv_pref;
  for (int i = 0; i < pref.length(); i++) {
    if (prior_calc(pref[i]) == 5) {
      stack_p.push(pref[i] - '0');
    }  else if ((prior_calc(pref[i]) < 5) && (prior_calc(pref[i]) > 0)) {
         int val1 = stack_p.get();
         stack_p.pop();
         int val2 = stack_p.get();
         stack_p.pop();
         if (prior_calc(pref[i]) == 1) {
            otvet = val2 + val1;
            stack_p.push(otvet);
         }  else if (prior_calc(pref[i]) == 2) {
              otvet = val2 - val1;
              stack_p.push(otvet);
            }  else if (prior_calc(pref[i]) == 3) {
                 otvet = val2 * val1;
                 stack_p.push(otvet);
               } else if (prior_calc(pref[i]) == 4) {
                   otvet = val2 / val1;
                   stack_p.push(otvet);
                 }
     }
  }
  otvet = stack_p.get();
  return otvet;
}
