/** 0-index */
template <typename A>
class SegTree {
  using VA = vector<A>;
  using FM = function<A(A,A)>;

  private:
  int n;
  VA tree;
  FM M;
  A dA;

  public:
  SegTree(const VA &a, const FM M, const A dA): M(M), dA(dA) {
    n = a.size();
    tree = VA(2*n);
    for (int i=0; i<n; i++) tree[i+n] = a[i];
    for (int i=n-1; i>0; i--) tree[i] = M(tree[i<<1], tree[i<<1|1]);
  }

  void update(int i, A v) {
    for (tree[i+=n]=v; i>1; i>>=1)
      tree[i>>1] = M(tree[i>>1<<1], tree[i>>1<<1|1]);
  }

  A query(int l, int r) {
    l += n; r += n;
    A resL = dA, resR = dA;
    for (int L=l,R=r; L<=R; L>>=1,R>>=1) {
      if (L&1) resL = M(resL, tree[L++]);
      if (~R&1) resR = M(tree[R--], resR);
    }
    return M(resL, resR);
  }
};
