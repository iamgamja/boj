/** 0-index */
template <typename A, typename B>
class LazySegTree {
  using VA = vector<A>;
  using VB = vector<B>;
  using M = function<A(A,A)>;
  using U = function<A(A,B)>;
  using C = function<B(B,B)>;

  private:
  int n;
  VA tree;
  VB lazy;
  M M;
  A dA;
  U U;
  B dB;
  C C;

  void apply(int i, B b) {
    // i에 b를 업데이트
    tree[i] = M(tree[i], b);
    if (i<n) lazy[i] = C(lazy[i], b);
  }

  void push(int i) {
    // i의 lazy를 자식에게 전파
    apply(i<<1, lazy[i]);
    apply(i<<1|1, lazy[i]);
    lazy[i] = dB;
  }

  void pull(int i) {
    // i의 값을 자식으로부터 계산
    tree[i] = M(tree[i<<1], tree[i<<1|1]);
  }

  void spread(int i) {
    // i의 조상에 대해 pull↑, push↓
    stack<int> s;
    while (i) {
      pull(i);
      s.push(i);
      i>>=1;
    }
    while (!s.empty()) {
      int now = s.top(); s.pop();
      push(now);
    }
  }

  public:
  SegTree(const V &a, M M, A dA, U U, B dB, C C): M(M), dA(dA), U(U), dB(dB), C(C) {
    n = a.size();
    tree = VA(2*n);
    lazy = VB(2*n, dB);
    for (int i=0; i<n; i++) tree[i+n] = a[i];
    for (int i=n-1; i>0; i--) tree[i] = M(tree[i<<1], tree[i<<1|1]);
  }

  // [l,r]
  void update(int l, int r, T v) {
    l += n; r += n;
    spread(l); spread(r);

    for (int L=l, R=r; L<=r; R>>=1,R>>=1) {
      if (L&1) apply(L++, v);
      if (~R&1) apply(R--, v);
    }

    spread(l); spread(r);
  }

  // [l,r]
  A query(int l, int r) {
    l += n; r += n;
    spread(l); spread(r);

    A res = dA;
    for (; l<=r; l>>=1,r>>=1) {
      if (l&1) res = M(res, tree[l++]);
      if (~r&1) res = M(res, tree[--r]);
    }
    return res;
  }
};
