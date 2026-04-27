#include "../../default.hpp"

/**
 * 0-index
 * 
 * requires class A:
 * - A has default constructor that returns identity
 * - A.M(A): merge. if one of them is identity, return the other.
 */
template <typename A>
class SegTree2d {
  using VA = vector<A>;
  using VVA = vector<VA>;

  private:
  i32 Y, X;
  VVA tree;

  A queryX(i32 y, i32 x1, i32 x2) {
    x1 += X; x2 += X;
    A resL = A(), resR = A();

    for (i32 L=x1, R=x2; L<=R; L>>=1, R>>=1) {
      if (L&1) resL = resL.M(tree[y][L++]);
      if (~R&1) resR = tree[y][R--].M(resR);
    }
    return resL.M(resR);
  }

  public:
  SegTree2d(const VVA &a) {
    Y = a.size();
    X = a[0].size();
    tree = VVA(2*Y, VA(2*X));
    for (i32 y=0; y<Y; y++) {
      for (i32 x=0; x<X; x++)
        tree[Y+y][X+x] = a[y][x];
      for (i32 x=X-1; x>0; x--)
        tree[Y+y][x] = tree[Y+y][x<<1].M(tree[Y+y][x<<1|1]);
    }
    for (i32 y=Y-1; y>0; y--)
      for (i32 x=0; x<2*X; x++)
        tree[y][x] = tree[y<<1][x].M(tree[y<<1|1][x]);
  }

  void update(i32 y_, i32 x_, A v) {
    tree[y_+=Y][x_+=X]=v;

    // 먼저 같은 y update
    for (i32 x=x_>>1; x; x>>=1)
      tree[y_][x] = tree[y_][x<<1].M(tree[y_][x<<1|1]);

    // 이제 y 올라가면서 update
    for (i32 y=y_>>1; y; y>>=1)
      for (i32 x=x_; x; x>>=1)
        tree[y][x] = tree[y<<1][x].M(tree[y<<1|1][x]);
  }

  A query(i32 y1, i32 x1, i32 y2, i32 x2) {
    y1 += Y; y2 += Y;
    A resL = A(), resR = A();

    for (i32 L=y1, R=y2; L<=R; L>>=1, R>>=1) {
      if (L&1) resL = resL.M(queryX(L++, x1, x2));
      if (~R&1) resR = queryX(R--, x1, x2).M(resR);
    }
    return resL.M(resR);
  }
};
