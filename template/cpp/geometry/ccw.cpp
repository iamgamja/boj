i64 ccw(const Point &a, const Point &b, const Point &c) {
  return (b-a)/(c-a);
}

template <typename T>
i32 sign(T v) {
  return (T(0) < v) - (v < T(0));
}

i32 sccw(const Point &a, const Point &b, const Point &c) {
  return sign(ccw(a,b,c));
}
