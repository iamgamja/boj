class UnionFind {
  private:
  vector<i32> p;

  public:
  // [0, e)
  UnionFind(i32 e) {
    p.resize(e);
    for (i32 i = 0; i < e; i++) p[i] = i;
  }

  i32 find(i32 x) {
    if (p[x] == x) return x;
    return p[x] = find(p[x]);
  }

  // O(logN)
  void merge(i32 a, i32 b) {
    i32 ar = find(a);
    i32 br = find(b);
    if (ar == br) return;
    p[br] = ar;
  }
};
