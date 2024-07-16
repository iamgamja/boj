/** 0-index */
template <typename A>
class SegTree2d {
  using VA = vector<A>;
  using VVA = vector<VA>;
  using FM = function<A(A,A)>;

  private:
  int Y, X;
  VVA tree;
  FM M;

  A queryX(int y, int x1, int x2) {
    x1 += X; x2 += X;
    A resL = A(), resR = A();

    for (int xL = x1, xR = x2; xL <= xR; xL >>= 1, xR >>= 1) {
      if (xL & 1) resL = M(resL, tree[y][xL++]);
      if (~xR & 1) resR = M(tree[y][xR--], resR);
    }
    return M(resL, resR);
  }

  public:
  SegTree2d(const VVA &a, const FM M): M(M) {
    Y = a.size();
    X = a[0].size();
    tree = VVA(2*Y, VA(2*X));
    for (int y=0; y<Y; y++) {
      for (int x=0; x<X; x++)
        tree[Y+y][X+x] = a[y][x];
      for (int x=X-1; x>0; x--)
        tree[Y+y][x] = M(tree[Y+y][x<<1], tree[Y+y][x<<1|1]);
    }
    for (int y=Y-1; y>0; y--)
      for (int x=0; x<2*X; x++)
        tree[y][x] = M(tree[y<<1][x], tree[y<<1|1][x]);
  }

  void update(int y_, int x_, A v) {
    tree[y_+=Y][x_+=X]=v;

    // 먼저 같은 y update
    for (int x=x_; x>1; x>>=1)
      tree[y_][x>>1] = M(tree[y_][x>>1<<1], tree[y_][x>>1<<1|1]);

    // 이제 y 올라가면서 update
    for (int y=y_>>1; y; y>>=1)
      for (int x=x_; x; x>>=1)
        tree[y][x] = M(tree[y<<1][x], tree[y<<1|1][x]);
  }

  A query(int y1, int x1, int y2, int x2) {
    y1 += Y; y2 += Y;
    A resL = A(), resR = A();

    for (int yL = y1, yR = y2; yL <= yR; yL >>= 1, yR >>= 1) {
      if (yL & 1) resL = M(resL, queryX(yL++, x1, x2));
      if (~yR & 1) resR = M(queryX(yR--, x1, x2), resR);
    }
    return M(resL, resR);
  }
};
