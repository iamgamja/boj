class Node {
  public:
  bool isI;
  i64 left, right, res, sum;

  Node(): isI(1), left(0), right(0), res(0), sum(0) {}
  Node(i64 x) { set(x); }
  Node(i64 left, i64 right, i64 res, i64 sum): isI(0), left(left), right(right), res(res), sum(sum) {}

  void set(i64 x) {
    isI = 0;
    left = right = res = sum = x;
  }

  friend istream& operator>>(istream& is, Node& node) {
    i64 x; is >> x;
    node.set(x);
    return is;
  }

  friend ostream& operator<<(ostream& os, Node& node) {
    return os << "Node(" << node.left << ", " << node.right << ", " << node.res << ", " << node.sum << ")";
  }

  Node operator+(Node o) {
    if (isI) return o;
    if (o.isI) return *this;
    return Node(
      max(left, sum + o.left),
      max(o.right, right + o.sum),
      max({res, o.res, right+o.left}),
      sum + o.sum
    );
  }
};
