#include "../default.hpp"

template<int MOD>
struct ModInt {
  i64 x;
  ModInt(i64 x = 0): x((x % MOD + MOD) % MOD) {}
  
  ModInt operator-() const { return ModInt(-x); }
  ModInt& operator+=(const ModInt& a) { if ((x += a.x) >= MOD) x -= MOD; return *this; }
  ModInt& operator-=(const ModInt& a) { if ((x += MOD - a.x) >= MOD) x -= MOD; return *this; }
  ModInt& operator*=(const ModInt& a) { (x *= a.x) %= MOD; return *this; }
  
  ModInt operator+(const ModInt& a) const { return ModInt(*this) += a; }
  ModInt operator-(const ModInt& a) const { return ModInt(*this) -= a; }
  ModInt operator*(const ModInt& a) const { return ModInt(*this) *= a; }
  
  bool operator==(const ModInt& a) const { return x == a.x; }
  bool operator!=(const ModInt& a) const { return x != a.x; }

  ModInt pow(i64 n) const {
    ModInt res(1), a(*this);
    while (n > 0) {
      if (n & 1) res *= a;
      a *= a;
      n >>= 1;
    }
    return res;
  }

  ModInt inv() const { return pow(MOD - 2); }
  
  ModInt& operator/=(const ModInt& a) { return *this *= a.inv(); }
  ModInt operator/(const ModInt& a) const { return ModInt(*this) /= a; }

  friend ostream& operator<<(ostream& os, const ModInt& a) { return os << a.x; }
  friend istream& operator>>(istream& is, ModInt& a) { i64 v; is >> v; a = ModInt(v); return is; }
};
