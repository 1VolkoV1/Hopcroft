#ifndef MINIMIZE_MIN_REGEX_AUTOMATA
#define MINIMIZE_MIN_REGEX_AUTOMATA
#include"common.hpp"
#include"AST.hpp"
#include"Automata.hpp"

bool eq(
  std::vector<std::vector<int>> a,
  std::vector<std::vector<int>> b
);
bool areInSame(
  int a, int b, std::vector<std::vector<int>> dic
);
void push(int item, std::vector<int>* set);
void pushIfFree(
  int item, std::vector<std::vector<int>> *dic
);
void add(
  int item_a,
  int item_b,
  bool apart,
  std::vector<std::vector<int>> *dic
);
Automata* minimize(Automata* A);
#endif