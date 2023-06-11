#ifndef mainfile
#include <bits/stdc++.h>
using namespace std;
#endif

/**
 * tree[node]: a[s, e] 범위의 op 값
 * 쿼리 범위: [l, r]
 *
 * 1-index
 */
#define op(a, b) ((a) + (b))
#define _default 0
template <typename T>
class SegmentTree {
  private:
  vector<T> a;
  int n;
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

  void _update(int node, int s, int e, int i, T v) {
    if (i < s || e < i)
      return;

    if (s == e) {
      tree[node] = v;
      return;
    }

    _update(node * 2, s, (s + e) / 2, i, v);
    _update(node * 2 + 1, (s + e) / 2 + 1, e, i, v);
    tree[node] = op(tree[node * 2], tree[node * 2 + 1]);
  }

  public:
  // 1-index
  SegmentTree(vector<T> &a_) {
    a = a_;
    n = a.size() - 1;
    auto tree_size = 1 << ((int)ceill(log2l(n)) + 1); // 2 ^ ⌈ lg n ⌉
    tree = vector<T>(tree_size, _default);
    _init(1, 1, n);
  }

  T query(int l, int r) {
    return _query(1, 1, n, l, r);
  }

  void update(int i, T v) {
    _update(1, 1, n, i, v);
  }
};