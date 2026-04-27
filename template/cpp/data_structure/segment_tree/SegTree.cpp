#include "../../default.hpp"

/**
 * 0-index
 * 
 * requires class A:
 * - A has default constructor that returns identity
 * - A.M(A): merge. if one of them is identity, return the other.
 */
template <typename A>
class SegTree {
  using VA = vector<A>;

  private:
  i32 n;
  VA tree;

  public:
  SegTree(const VA &a) {
    n = a.size();
    tree = VA(2*n);
    for (i32 i=0; i<n; i++) tree[n+i] = a[i];
    for (i32 i=n-1; i>0; i--) tree[i] = tree[i<<1].M(tree[i<<1|1]);
  }

  void update(i32 i, A v) {
    assert(0 <= i && i < n);

    for (tree[i+=n]=v, i>>=1; i; i>>=1)
      tree[i] = tree[i<<1].M(tree[i<<1|1]);
  }

  A query(i32 l, i32 r) {
    if (!(0 <= l && l <= r && r < n)) return A();
    
    l += n; r += n;
    A resL = A(), resR = A();
    for (i32 L=l,R=r; L<=R; L>>=1,R>>=1) {
      if (L&1) resL = resL.M(tree[L++]);
      if (~R&1) resR = tree[R--].M(resR);
    }
    return resL.M(resR);
  }
};
