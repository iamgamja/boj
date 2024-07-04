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
};
