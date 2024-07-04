/** 0-index */
template <typename T>
class SegTree {
  using V = vector<T>;
  using OP = function<T(T,T)>;

  private:
  i32 n;
  V tree;
  OP op;

  public:
  SegTree(const V &a, OP op): op(op) {
    n = a.size();
    tree = vector<T>(2*n);
    for (i32 i=0; i<n; i++) tree[i+n] = a[i];
    for (i32 i=n-1; i>0; i--) tree[i] = op(tree[i<<1], tree[i<<1|1]);
  }

  void update(i32 i, T v) {
    for (tree[i+=n]=v; i>1; i>>=1)
      tree[i>>1] = op(tree[i], tree[i^1]);
  }

  T query(i32 l, i32 r) {
    T res = 0; // 여기 기본값이 0이 아닐수도?
    for (l+=n,r+=n+1; l<r; l>>=1,r>>=1) {
      if (l&1) res = op(res, tree[l++]);
      if (r&1) res = op(res, tree[--r]);
    }
    return res;
  }
};
