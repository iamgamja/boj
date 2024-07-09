bool iscross(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
  auto r1 = sccw(a1,a2,b1)*sccw(a1,a2,b2);
  auto r2 = sccw(b1,b2,a1)*sccw(b1,b2,a2);
  if (r1==0 && r2==0) {
    // 네 점이 모두 일직선이거나 끝 점 하나를 공유
    // 아래 코드로 끝 점 하나를 공유할 경우도 처리 가능하므로 무시
    if (max(a1,a2) < min(b1,b2)) return 0;
    if (max(b1,b2) < min(a1,a2)) return 0;
    return 1;
  }
  return r1<=0 && r2<=0;
}

bool iscross_exclude_boundary(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
  auto r1 = sccw(a1,a2,b1)*sccw(a1,a2,b2);
  auto r2 = sccw(b1,b2,a1)*sccw(b1,b2,a2);
  if (r1==0 && r2==0) {
    // 네 점이 모두 일직선이거나 끝 점 하나를 공유
    // 아래 코드로 끝 점 하나를 공유할 경우도 처리 가능하므로 무시
    if (max(a1,a2) <= min(b1,b2)) return 0;
    if (max(b1,b2) <= min(a1,a2)) return 0;
    return 1;
  }
  return r1<0 && r2<0;
}
