class Point {
  public:
  int x, y;

  Point(): x(0), y(0) {}
  Point(i32 x, i32 y) : x(x), y(y) {}

  friend istream& operator>>(istream& is, Point& p) {
    return is >> p.x >> p.y;
  }

  friend ostream& operator<<(ostream& os, const Point& p) {
    return os << "(" << p.x << ", " << p.y << ")";
  }

  Point operator+(const Point& o) const {
    return Point(x+o.x, y+o.y);
  }
  Point operator-(const Point& o) const {
    return Point(x-o.x, y-o.y);
  }
  Point operator-() {
    return Point(-x, -y);
  }
  i64 operator*(const Point& o) {
    return (i64)x*o.x + (i64)y*o.y;
  }
  i64 operator/(const Point& o) {
    return (i64)x*o.y - (i64)y*o.x;
  }

  auto operator<=>(const Point& o) const {
    return (x <=> o.x)!=0 ? (x <=> o.x) : (y <=> o.y);
  }
};
