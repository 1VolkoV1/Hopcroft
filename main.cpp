#include<iostream>
#include<vector>
#include"common.cpp"
#include"AST.cpp"
#include"Automata.cpp"
#include"minimize.cpp"

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


int testFromAST() {
  AST* left = createStar("a");
  AST* right = createHash();

  AST* ast = new AST;
  ast->type = cat_node;

  ast->left = left;
  ast->right = right;
  
  ast->fpos = (
    left->nullable
      ? concat(left->fpos, right->fpos)
      : left->fpos
  );
  ast->lpos = (
    right->nullable
      ? concat(left->lpos, right->lpos)
      : right->lpos
  );
  ast->nullable = (
    left->nullable && right->nullable
  );

  std::vector<std::vector<int>> followpos = FollowPos(ast);
  std::cout << "followpos:\n";
  for (int i = 0; i < followpos.size(); i++) {
    Automata::printVec(std::cout, followpos[i]);
    std::cout << std::endl;
  }

  Automata* B = fromAST(ast);

  std::cout << *B << std::endl;
  std::cout << "Want to test your automata?" << std::endl;

  char* str = (char*)malloc(1024 * sizeof(char));
  std::cin >> str;
  std::cout << (B->test((const char*)str) ? "1\n" : "0\n");
  
  return 0;
}

int minimization() {
  Automata A(
    { 'a' },
    { 0, 1, 2, 3 },
    0,
    { 0, 2 },
    { { 1 }, { 2 }, { 3 }, { 0 } }
  );
  std::cout << A;
  Automata* B = minimize(&A);
  std::cout << *B;
  return 0;
}

int interactive() {
  char* str = (char*)malloc(1024 * sizeof(char));

  std::cin >> str;

  AST* ast = fromREGEX(str);

  // logging
  /*
    std::cout << "ast: " << std::endl;
    printAST(ast);
    std::cout << std::endl;
    std::vector<std::vector<int>> followpos = FollowPos(ast);
    std::cout << "followpos:\n";
    for (int i = 0; i < followpos.size(); i++) {
      Automata::printVec(std::cout, followpos[i]);
      std::cout << std::endl;
    }
  */

  Automata* B = fromAST(ast);

  std::cout << *B << std::endl;
  std::cout << "Want to test your automata?" << std::endl;

  std::cin >> str;
  std::cout << (B->test((const char*)str) ? "1\n" : "0\n");
  return 0;
}

int result() {
  char* str = (char*)malloc(1024 * sizeof(char));
  std::cin >> str;
  Automata* A = minFromREGEX(str);
  std::cout << *A;
  return 0;
}


int main(int argc, char** argv) {
  result();



  return 0;
}