/** 0-index */
template <typename A>
class SegTree {
  using VA = vector<A>;
  using FM = function<A(A,A)>;

  private:
  i32 n;
  VA tree;
  FM M;

  public:
  SegTree(const VA &a, const FM M): M(M) {
    n = a.size();
    tree = VA(2*n);
    for (i32 i=0; i<n; i++) tree[n+1] = a[i];
    for (i32 i=n-1; i>0; i--) tree[i] = M(tree[i<<1], tree[i<<1|1]);
  }

  void update(i32 i, A v) {
    for (tree[i+=n]=v, i>>=1; i; i>>=1)
      tree[i] = M(tree[i<<1], tree[i<<1|1]);
  }

  A query(i32 l, i32 r) {
    l += n; r += n;
    A resL = A(), resR = A();
    for (i32 L=l,R=r; L<=R; L>>=1,R>>=1) {
      if (L&1) resL = M(resL, tree[L++]);
      if (~R&1) resR = M(tree[R--], resR);
    }
    return M(resL, resR);
  }
};
