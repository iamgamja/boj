template<typename A>
/** sum, 0-index */
class FenwickTree {
  using VA = vector<A>;

  private:
  VA tree;
  int n;

  /** [1, r] */
  A prefixQuery(i32 i) {
    i++; // 1-index
    A res = A();
    while (i) {
      res += tree[i];
      i -= i&-i;
    }
    return res;
  }

  public:
  FenwickTree(const VA &a) {
    n = a.size();
    tree = VA(n+1); // 1-index
    for (i32 i=0; i<n; i++)
      update(i, a[i]);
  }

  void update(i32 i, A v) {
    A diff = v - query(i,i);
    i++; // 1-index
    while (i<=n) {
      tree[i] += diff;
      i += i&-i;
    }
  }

  /** [l, r] */
  A query(i32 l, i32 r) {
    return prefixQuery(r) - prefixQuery(l-1);
  }
};
