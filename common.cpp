#include<vector>
#include"common.hpp"

int vecInVecSet(
  std::vector<int> search,
  std::vector<std::vector<int>> set
) {
  for (int i = 0; i < set.size(); i++) {
    bool match = true;
    if (search.size() != set[i].size()) match = false;
    for (int j = 0; (j < search.size()) && match; j++) {
      if (search[j] != set[i][j]) match = false;
    }
    if (match) return i;
  }
  return -1;
}