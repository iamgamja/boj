template <typename T>
i32 sign(T val) {
  return (T(0) < val) - (val < T(0));
}

i64 ccw(const Point& a, const Point& b, const Point& c) {
  return (b-a)/(c-a);
}

i32 sccw(const Point& a, const Point& b, const Point& c) {
  return sign(ccw(a,b,c));
}
