#include<algorithm>
#include<iostream>
#include<cstring>
#include"AST.hpp"

/**
 * Global variable used for leaf numbers
 */
int pos;

std::vector<int> concat(
  std::vector<int> a, std::vector<int> b
) {
  if (a.empty()) return b; 
  if (b.empty()) return a; 
  a.insert(a.end(), b.begin(), b.end());
  // required for making unique element
  std::sort(a.begin(), a.end());
  //for finding unique element within vector
  a.erase(std::unique(a.begin(), a.end()), a.end());
  return a;
}

AST* createLeaf(int val) {
  AST* leaf = new AST;
  std::vector<int>fpos { pos };
  std::vector<int>lpos { pos };

  leaf->type = leaf_node;
  leaf->value = val;
  leaf->fpos = fpos;
  leaf->lpos = lpos;
  leaf->nullable = false;

  pos++;
  return leaf;
}

AST* createHash() {
  AST* hash = new AST;
  std::vector<int>fpos { pos };
  std::vector<int>lpos { pos };

  hash->type = hash_node;
  hash->fpos = fpos;
  hash->lpos = lpos;
  hash->nullable = false;

  pos++;
  return hash;
}
d
AST* createCat(
  const char* left,
  const char* right,
  bool isHash
) {
  AST* node = new AST;
  node->type = cat_node;

  AST* leftChild = fromString(left);
  AST* rightChild = (
    isHash
      ? createHash()
      : fromString(right)
  );

  node->left = leftChild;
  node->right = rightChild;
  
  node->fpos = (
    leftChild->nullable
      ? concat(leftChild->fpos, rightChild->fpos)
      : leftChild->fpos
  );
  node->lpos = (
    rightChild->nullable
      ? concat(leftChild->lpos, rightChild->lpos)
      : rightChild->lpos
  );
  node->nullable = (
    leftChild->nullable && rightChild->nullable
  );

  return node;
}

AST* createOr(const char* left, const char* right) {
  AST* node = new AST;
  node->type = or_node;

  AST* leftChild = fromString(left);
  AST* rightChild = fromString(right);

  node->left = leftChild;
  node->right = rightChild;
  
  node->fpos = concat(
    leftChild->fpos, rightChild->fpos
  );
  node->lpos = concat(
    leftChild->lpos, rightChild->lpos
  );
  node->nullable = leftChild->nullable
    || rightChild->nullable;

  return node;
}

AST* createStar(const char* content) {
  AST* node = new AST;
  node->type = star_node;

  AST* child = fromString(content);

  node->left = child;
  
  node->fpos = child->fpos;
  node->lpos = child->lpos;
  node->nullable = true;

  return node;
}

