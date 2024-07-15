template<typename A>
/** sum, 0-index */
class FenwickTree {
  using VA = vector<A>;

  private:
  VA tree;
  int n;

  public:
  FenwickTree(const VA &a) {
    n = a.size();
    tree = VA(n+1); // 1-index
    for (int i=0; i<n; i++)
      update(i, a[i]);
  }

  void update(int i, A v) {
    A diff = v - query(i,i);
    i++; // 1-index
    while (i<=n) {
      tree[i] += diff;
      i += i&-i;
    }
  }

  /** [1, r] */
  A query(int i) {
    i++; // 1-index
    A res = A();
    while (i) {
      res += tree[i];
      i -= i&-i;
    }
    return res;
  }

  /** [l, r] */
  A query(int l, int r) {
    return query(r) - query(l-1);
  }
};
