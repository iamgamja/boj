template<typename A>
/** sum, 0-index */
class FenwickTree2d {
  using VA = vector<A>;
  using VVA = vector<VA>;

  private:
  VVA tree;
  int Y;
  int X;

  A prefixQuery(int y_, int x_) {
    y_++; x_++; // 1-index
    A res = A();
    for (int y=y_; y; y-=y&-y)
      for (int x=x_; x; x-=x&-x)
        res += tree[y][x];
    return res;
  }

  public:
  FenwickTree2d(const VVA &a) {
    Y = a.size();
    X = a[0].size();
    tree = VVA(Y+1, VA(X+1)); // 1-index
    for (int y=0; y<Y; y++)
      for (int x=0; x<X; x++)
        update(y, x, a[y][x]);
  }

  void update(int y_, int x_, A v) {
    A diff = v - query(y_,x_,y_,x_);
    y_++; x_++; // 1-index
    for (int y=y_; y<=Y; y+=y&-y)
      for (int x=x_; x<=X; x+=x&-x)
        tree[y][x] += diff;
  }

  A query(int y1, int x1, int y2, int x2) {
    return prefixQuery(y2,x2) - prefixQuery(y2,x1-1) - prefixQuery(y1-1,x2) + prefixQuery(y1-1,x1-1);
  }
};
