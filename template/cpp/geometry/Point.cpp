class Point {
  public:
  int x, y;

  Point(): x(0), y(0) {}
  Point(int x, int y) : x(x), y(y) {}

  friend istream& operator>>(istream& is, Point& p) {
    is >> p.x >> p.y;
    return is;
  }

  friend ostream& operator<<(ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
  }

  Point& operator+(const Point& a, const Point& b) {
    return Point(a.x+b.x,a.y+b.y);
  }
  Point& operator-(const Point& a, const Point& b) {
    return Point(a.x-b.x,a.y-b.y);
  }
  i64 operator*(const Point& a, const Point& b) {
    return (i64)a.x*b.x+(i64)a.y*b.y;
  }
  i64 operator/(const Point& a, const Point& b) {
    return (i64)a.x*b.y-(i64)a.y*b.x;
  }
};
