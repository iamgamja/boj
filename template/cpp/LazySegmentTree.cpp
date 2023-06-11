#ifndef mainfile
#include <bits/stdc++.h>
using namespace std;
#endif

/**
 * tree[node]: a[s, e] 범위의 op 값
 * 쿼리 범위: [l, r]
 *
 * lazy[node]: tree[node]의 lazy값
 *
 * opop(a, b) = op(a, op(a, ...)) 를 b번 반복
 *
 * 1-index
 */
#define op(a, b) ((a) + (b))
#define opop(a, b) ((a) * (b))
#define _default 0
template <typename T>
class LazySegmentTree {
  private:
  vector<T> a;
  int n;
  vector<T> lazy;
  vector<T> tree;

  void _init(int node, int s, int e) {
    if (s == e) {
      tree[node] = a[s];
    } else {
      _init(node * 2, s, (s + e) / 2);
      _init(node * 2 + 1, (s + e) / 2 + 1, e);
      tree[node] = op(tree[node * 2], tree[node * 2 + 1]);
    }
  }

  T _query(int node, int s, int e, int l, int r) {
    // update lazy
    if (lazy[node] != _default) {
      tree[node] = op(tree[node], opop(lazy[node], e - s + 1));
      if (s != e) {
        lazy[node * 2] = op(lazy[node * 2], lazy[node]);
        lazy[node * 2 + 1] = op(lazy[node * 2 + 1], lazy[node]);
      }
      lazy[node] = _default;
    }

    // 범위를 벗어남
    if (e < l || r < s)
      return _default;

    // 포함
    if (l <= s && e <= r) {
      return tree[node];
    }

    // 적당히 양쪽 계산 후 op
    auto tmp1 = _query(node * 2, s, (s + e) / 2, l, r);
    auto tmp2 = _query(node * 2 + 1, (s + e) / 2 + 1, e, l, r);
    return op(tmp1, tmp2);
  }

  void _update(int node, int s, int e, int i1, int i2, T diff) {
    // update lazy
    if (lazy[node] != _default) {
      tree[node] = op(tree[node], opop(lazy[node], e - s + 1));
      if (s != e) {
        lazy[node * 2] = op(lazy[node * 2], lazy[node]);
        lazy[node * 2 + 1] = op(lazy[node * 2 + 1], lazy[node]);
      }
      lazy[node] = _default;
    }

    // 범위를 벗어남
    if (i2 < s || e < i1)
      return;

    // 포함
    if (i1 <= s && e <= i2) {
      tree[node] = op(tree[node], opop(diff, e - s + 1));
      if (s != e) {
        lazy[node * 2] = op(lazy[node * 2], diff);
        lazy[node * 2 + 1] = op(lazy[node * 2 + 1], diff);
      }
      return;
    }

    _update(node * 2, s, (s + e) / 2, i1, i2, diff);
    _update(node * 2 + 1, (s + e) / 2 + 1, e, i1, i2, diff);
    tree[node] = op(tree[node * 2], tree[node * 2 + 1]);
  }

  public:
  // 1-index
  LazySegmentTree(vector<T> &a_) {
    a = a_;
    n = a.size() - 1;
    auto tree_size = 1 << ((int)ceill(log2l(n)) + 1); // 2 ^ ⌈ lg n ⌉
    tree = vector<T>(tree_size, _default);
    lazy = vector<T>(tree_size, _default); // init 0
    _init(1, 1, n);
  }

  T query(int l, int r) {
    return _query(1, 1, n, l, r);
  }

  void update(int i1, int i2, T diff) {
    _update(1, 1, n, i1, i2, diff);
  }
};