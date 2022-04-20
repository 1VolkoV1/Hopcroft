#ifndef AST_MIN_REGEX_AUTOMATA
#define AST_MIN_REGEX_AUTOMATA
AST* createLeaf(int val);
AST* createHash();
AST* createStar(const char* content);
AST* createOr(const char* left, const char* right);
AST* createCat(
  const char* left,
  const char* right,
  bool isHash
);
AST* fromString(const char* str);

AST* fromREGEX(const char* regex);
std::vector<int> concat(
  std::vector<int> a, std::vector<int> b
);
void printAST(AST* ast);
std::vector<int> alphabet(AST* ast);
void putinmap(std::vector<int> *map, AST* ast);
std::vector<int> CharValueMap(AST* ast);
void computeFpos(
  std::vector<std::vector<int>> *followpos, AST* ast
);
std::vector<std::vector<int>> FollowPos(AST* ast);
#endif