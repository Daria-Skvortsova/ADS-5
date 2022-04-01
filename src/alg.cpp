// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int priority(char op) {
  switch (op) {
  case '(':
    return 0;
  case ')':
    return 1;
  case '+':case'-':
    return 2;
  case '*':case'/':
    return 3;
  default:
    return 4;
  }
}
int prior_calc(char value) {
  switch (value) {
  case '+':
    return 1;
  case '-':
    return 2;
  case '*':
    return 3;
  case '/':
    return 4;
  case ' ':
    return 0;
  default:
    return 5;
  }
}
std::string infx2pstfx(std::string inf) {
  std::string pref;
  TStack<char, 100> stack;
  for (int i = 0; i < inf.length(); i++) {
    if (priority(inf[i]) == 4) {
      if (priority(inf[i+1]) == 4) {
        pref.push_back(inf[i]);
        while (priority(inf[i + 1]) == 4 && i+1 < inf.length()) {
          pref.push_back(inf[i+1]);
          i++;
        }
        pref.push_back(' ');
      }  else {
           pref.push_back(inf[i]);
           pref.push_back(' ');
        }
      }  else {
           if (priority(inf[i]) == 0) {
             stack.push(inf[i]);
           }  else if (priority(inf[i]) > priority(stack.get())) {
                stack.push(inf[i]);
              }  else if (stack.isEmpty()) {
                   stack.push(inf[i]);
                 }  else if (priority(inf[i]) == 1) {
                      while (priority(stack.get()) != 0) {
                        pref.push_back(stack.get());
                        pref.push_back(' ');
                        stack.pop();
                      }
                      stack.pop();
                    }  else if (priority(inf[i]) <= priority(stack.get())) {
                         while ((priority(stack.get()) > 1) &&
                          !stack.isEmpty()) {
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
    std::string proverka = "";
    while (prior_calc(pref[i]) == 5) {
      proverka.push_back(pref[i]);
      i++;
    }
    if (proverka != "") {
      stack_p.push(std::stoi(proverka));
    }
    if ((prior_calc(pref[i]) < 5) && (prior_calc(pref[i]) > 0)) {
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
          }  else if (prior_calc(pref[i]) == 4) {
               otvet = val2 / val1;
               stack_p.push(otvet);
             }
    }
  }
  otvet = stack_p.get();
  return otvet;
}
