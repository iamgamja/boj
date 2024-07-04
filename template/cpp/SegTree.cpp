/** 0-index */
template <typename T>
class SegTree {
  using V = vector<T>;
  using OP = function<T(T,T)>;

  private:
  int n;
  V tree;
  OP op;

  public:
  SegTree(const V &a, OP op): op(op) {
    n = a.size();
    tree = vector<T>(2*n);
    for (int i=0; i<n; i++) tree[i+n] = a[i];
    for (int i=n-1; i>0; i--) tree[i] = op(tree[i<<1], tree[i<<1|1]);
  }

  void update(int i, T v) {
    for (tree[i+=n]=v; i>1; i>>=1)
      tree[i>>1] = op(tree[i], tree[i^1]);
  }

  T query(int l, int r) {
    T res = 0;
    for (l+=n,r+=n+1; l<r; l>>=1,r>>=1) {
      if (l&1) res = op(res, tree[l++]);
      if (r&1) res = op(res, tree[--r]);
    }
    return res;
  }
};
