#include<algorithm>
#include<iostream>
#include<vector>
#include"Automata.hpp"

Automata::Automata(
  std::vector<int> __T,
  std::vector<int> __Q,
  int __q0,
  std::vector<int> __Q_f,
  std::vector<std::vector<int>> __f
) {
  T = __T;
  Q = __Q;
  q0 = __q0;
  Q_f = __Q_f;
  f = __f;
}

bool Automata::test(const char* word) {
  int q_cur = q0;
  int i = 0;
  char c;
  while (c = word[i++]) {
    // 1. find corresponding charcode in alphabet
    auto search = std::find(T.begin(), T.end(), c);
    if (search == T.end()) return false;
    int charcode = std::distance(T.begin(), search);

    // 2. check if curstate has edge with that char
    if (f.size() < q_cur) return false;
    if (f[q_cur].size() < charcode) return false;
    q_cur = f[q_cur][charcode];
    if (q_cur < 0) return false;
  }

  // 3. check if we are in final state
  auto search = std::find(
    Q_f.begin(), Q_f.end(), q_cur
  );
  return search != Q_f.end();
}

const char* Automata::match(const char* word) {
  int q_cur = q0;
  int i = 0;
  char c;
  while (c = word[i++]) {
    // 1. find corresponding charcode in alphabet
    auto search = std::find(T.begin(), T.end(), c);
    if (search == T.end()) return nullptr;
    int charcode = std::distance(T.begin(), search);

    // 2. check if curstate has edge with that char
    if (f.size() < q_cur) return nullptr;
    if (f[q_cur].size() < charcode) return nullptr;
    q_cur = f[q_cur][charcode];
    if (q_cur < 0) return nullptr;

    // 3. check if we are in final state
    auto search2 = std::find(
      Q_f.begin(), Q_f.end(), q_cur
    );
    if (search2 != Q_f.end()) return &word[i - 1];
  }

  return nullptr;
}

Automata* fromAST(AST* ast) {
  std::vector<int> T = alphabet(ast);
  std::vector<int> Q, Q_f;
  int q0 = 0;
  std::vector<std::vector<int>> f;

  int endPos = ast->lpos[0];

  std::vector<std::vector<int>> firstPosForState = {
    ast->fpos
  };
  f.push_back({});
  Q.push_back(Q.size());


  std::vector<int> charvaluemap = CharValueMap(ast);
  std::vector<std::vector<int>> followpos = FollowPos(ast);

  // logging
  /*
    std::cout << "followpos:\n";
    for (int i = 0; i < followpos.size(); i++) {
      Automata::printVec(std::cout, followpos[i]);
      std::cout << std::endl;
    }
  */

  int i = 0;
  while (i < firstPosForState.size()) {
    std::vector<int> curin = firstPosForState[i];
    f[i].resize(T.size());

    // logging
    /*
      std::cout << "for state ";
      for (int t = 0; t < curin.size(); t++) std::cout << curin[t];
      std::cout << std::endl;
    */

    for (int j = 0; j < T.size(); j++) {
      int charvalue = T[j];
      std::vector<int> curout = {};

      // Trash state
      if (curin.empty()) f[i][j] = i;

      for (int k = 0; k < curin.size(); k++) {
        int fpos = curin[k];
        if (charvalue == charvaluemap[fpos])
          curout = concat(curout, followpos[fpos]);
      }
      std::sort(curout.begin(), curout.end());

      auto idx = vecInVecSet(curout, firstPosForState);
      if (idx == -1) {
        firstPosForState.push_back(curout);
        idx = vecInVecSet(curout, firstPosForState);

        Q.push_back(Q.size());
        f.push_back({});

        f[i][j] = idx;
      }
      else { f[i][j] = idx; }

      // final states
      if (
        std::find(
          curout.begin(), curout.end(), endPos
        ) != curout.end()
      ) Q_f.push_back(idx);
    }
    i++;
  }

  return new Automata(T, Q, q0, Q_f, f);
}
