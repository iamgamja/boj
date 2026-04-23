#include "../default.hpp"
#include "Point.cpp"
#include "../util/sign.cpp"

i64 ccw(const Point &a, const Point &b, const Point &c) {
  return (b-a)/(c-a);
}

i32 sccw(const Point &a, const Point &b, const Point &c) {
  return sign(ccw(a,b,c));
}
