template<typename A>
/** 0-index */
class FenwickTree {
  using VA = vector<A>;
  using FM = function<A(A,A)>;
  using FnM = function<A(A,A)>;

  private:
  VA tree;
  int n;
  FM M;
  FnM nM;

  public:
  FenwickTree(const VA &a, const FM M, const FnM nM): M(M), nM(nM) {
    n = a.size();
    tree = VA(n+1); // 1-index
    for (int i=0; i<n; i++)
      update(i, a[i]);
  }

  void update(int i, A v) {
    A diff = nM(v, query(i,i));
    i++; // 1-index
    while (i<=n) {
      tree[i] = M(tree[i], diff);
      i += i&-i;
    }
  }

  /** [1, r] */
  A query(int i) {
    i++; // 1-index
    A res = A();
    while (i) {
      res = M(res, tree[i]);
      i -= i&-i;
    }
    return res;
  }

  /** [l, r] */
  A query(int l, int r) {
    return nM(query(r), query(l-1));
  }
};
