#include<iostream>
#include<vector>

#include"Automata.cpp"

//test automata's work on input word:
int testFromAutomata() {
  Automata A(
    { 'a' },
    { 0, 1 },
    0,
    { 0 },
    { { 1 }, { 0 } }
  );
  char* str = (char*)malloc(1024 * sizeof(char));
  std::cin >> str;

  std::cout << (A.test((const char*)str) ? "1\n" : "0\n");

  std::cout << A << std::endl;
  return 0;
}

int main(int argc, char** argv) {
  testFromAutomata();

  return 0;
}