#include <../default.hpp>

VVI scc(const VVI &G, i32 V) {
  VVI revG(V);
  for (i32 i=0; i<V; i++)
    for (i32 j: G[i])
      revG[j].push_back(i);

  VI visit(V);
  stack<i32> S;
  for (i32 i=0; i<V; i++) {
    if (visit[i]) continue;

    auto dfs = [&](auto self, i32 i) -> void {
      visit[i] = 1;
      for (auto nxt: G[i]) {
        if (visit[nxt]) continue;

        self(self, nxt);
      }

      S.push(i);
    };
    dfs(dfs, i);
  }

  // dfs revG
  VVI res;
  visit.assign(V, 0);
  while (!S.empty()) {
    i32 i = S.top(); S.pop();
    if (visit[i]) continue;

    VI now_scc;
    
    auto dfs = [&](auto self, i32 i) -> void {
      visit[i] = 1;
      now_scc.push_back(i);

      for (auto nxt: revG[i]) {
        if (visit[nxt]) continue;

        self(self, nxt);
      }
    };
    dfs(dfs, i);

    res.push_back(now_scc);
  }

  return res;
}
