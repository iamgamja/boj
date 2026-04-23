#include "../default.hpp"

#include "getscc.cpp"

using var2SAT = pair<i32, bool>;
using term2SAT = pair<var2SAT, var2SAT>;

pair<bool, VI> solve2sat(i32 N, const vector<term2SAT> &A) {
  // i: xi (0-index)
  // N+i: not xi (0-index)
  VVI G(2*N);

  for (auto &term: A) {
    auto [i1, v1] = term.first;
    auto [i2, v2] = term.second;

    i32 x1 = v1 ? i1 : i1 + N;
    i32 nx1 = !v1 ? i1 : i1 + N;
    i32 x2 = v2 ? i2 : i2 + N;
    i32 nx2 = !v2 ? i2 : i2 + N;

    G[nx1].push_back(x2);
    G[nx2].push_back(x1);
  }

  auto scc = getscc(G, 2*N);
  VI scc_idx(2*N);
  for (i32 i=0; i<scc.size(); i++)
    for (auto x: scc[i])
      scc_idx[x] = i;

  for (i32 x=0; x<N; x++)
    if (scc_idx[x] == scc_idx[x >= N ? x-N : x+N]) {
      return {0, VI()};
    }

  // Yes
  VI res(N, -1);
  for (auto &s: scc) {
    for (auto x: s) {
      i32 i = x >= N ? x-N : x;
      i32 v = x >= N ? 1 : 0; // 거짓으로 설정
      if (res[i] == -1) res[i] = v;
    }
  }

  return {1, res};
}
