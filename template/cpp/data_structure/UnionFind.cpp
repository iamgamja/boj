class UnionFind {
  private:
  vector<i32> p;
  vector<i32> d;

  public:
  // [0, e]
  UnionFind(i32 e) {
    p.resize(e+1);
    d.resize(e+1);
    for (i32 i = 0; i <= e; i++) {
      p[i] = i;
      d[i] = 1;
    }
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

    if (d[ar] < d[br]) swap(ar, br);
    
    p[br] = ar; // a에 b 합치기
    if (d[ar] == d[br]) d[ar]++;
  }
};
