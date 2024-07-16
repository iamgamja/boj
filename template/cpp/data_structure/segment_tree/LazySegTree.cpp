/** 0-index */
template <typename A, typename B>
class LazySegTree {
  using VA = vector<A>;
  using VB = vector<B>;
  using FM = function<A(A,A)>;
  using FU = function<A(A,B)>;
  using FC = function<B(B,B)>;

  // private:
  public:
  int n;
  VA tree;
  VB lazy;
  FM M;
  FU U;
  FC C;

  void apply(const int i, const B b) {
    // i에 b를 업데이트
    tree[i] = U(tree[i], b);
    if (i<n) lazy[i] = C(lazy[i], b);
  }

  void push(const int i) {
    // i의 lazy를 자식에게 전파
    apply(i<<1, lazy[i]);
    apply(i<<1|1, lazy[i]);
    lazy[i] = B();
  }

  void pull(const int i) {
    // i의 값을 자식으로부터 계산
    tree[i] = M(tree[i<<1], tree[i<<1|1]);
  }

  void calculateAncestorLazy(int i) {
    // i의 조상에 대해 push↓
    stack<int> s;
    while (i>>=1) {
      s.push(i);
    }
    while (!s.empty()) {
      int now = s.top(); s.pop();
      push(now);
    }
  }

  void calculateAncestorTree(int i) {
    // i의 조상 중 이번에 수정되지 않은
    // <=> lazy가 비어있는 노드에 대해 pull↑
    while (i>>=1) {
      if (lazy[i] == B())
        pull(i);
    }
  }

  public:
  LazySegTree(const VA &a, const FM M, const FU U, const FC C): M(M), U(U), C(C) {
    n = a.size();
    tree = VA(2*n);
    lazy = VB(2*n, B());
    for (int i=0; i<n; i++) tree[i+n] = a[i];
    for (int i=n-1; i>0; i--) pull(i);
  }

  // [l,r]
  void update(int l, int r, const B v) {
    l += n; r += n;
    calculateAncestorLazy(l);
    calculateAncestorLazy(r);

    for (int L=l,R=r; L<=R; L>>=1,R>>=1) {
      if (L&1) apply(L++, v);
      if (~R&1) apply(R--, v);
    }

    calculateAncestorTree(l);
    calculateAncestorTree(r);
  }

  // [l,r]
  A query(int l, int r) {
    l += n; r += n;
    calculateAncestorLazy(l);
    calculateAncestorLazy(r);

    A resL = A(), resR = A();
    for (int L=l,R=r; L<=R; L>>=1,R>>=1) {
      if (L&1) resL = M(resL, tree[L++]);
      if (~R&1) resR = M(tree[R--], resR);
    }
    return M(resL, resR);
  }
};
