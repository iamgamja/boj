class Point {
  public:
  i64 x, y;

  Point(): x(0), y(0) {}
  Point(i64 x, i64 y): x(x), y(y) {}

  friend istream& operator>>(istream &is, Point &p) {
    return is >> p.x >> p.y;
  }

  friend ostream& operator<<(ostream &os, const Point &p) {
    return os << "(" << p.x << ", " << p.y << ")";
  }

  Point operator+(const Point &o) const {
    return Point(x+o.x, y+o.y);
  }
  Point operator-(const Point &o) const {
    return Point(x-o.x, y-o.y);
  }
  Point operator-() const {
    return Point(-x, -y);
  }
  /** 내적 */
  i64 operator*(const Point &o) const {
    return x*o.x + y*o.y;
  }
  /** 외적 */
  i64 operator/(const Point &o) const {
    return x*o.y - y*o.x;
  }

  auto operator<=>(const Point &o) const {
    return (x <=> o.x) != 0 ? (x <=> o.x) : (y <=> o.y);
  }
  bool operator==(const Point &o) const {
    return x == o.x && y == o.y;
  }
};
