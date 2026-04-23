#include "../default.hpp"

template <typename T>
struct Matrix {
  using VT = vector<T>;
  using VVT = vector<VT>;

  i32 R, C;
  VVT A;

  Matrix(i32 N): R(N), C(N), A(VVT(N, VT(N))) {};
  Matrix(i32 R, i32 C): R(R), C(C), A(VVT(R, VT(C))) {};
  Matrix(VVT A): A(A), R(A.size()), C(A[0].size()) {};

  Matrix operator+(const Matrix &o) const {
    assert(R == o.R && C == o.C);
    
    Matrix res(R, C);
    for (i32 i=0; i<R; i++)
      for (i32 j=0; j<C; j++)
        res[i][j] = A[i][j] + o[i][j];

    return res;
  }

  Matrix operator-(const Matrix &o) const {
    assert(R == o.R && C == o.C);
    
    Matrix res(R, C);
    for (i32 i=0; i<R; i++)
      for (i32 j=0; j<C; j++)
        res[i][j] = A[i][j] - o[i][j];

    return res;
  }

  Matrix operator*(const T &o) const {
    Matrix res(R, C);
    for (i32 i=0; i<R; i++)
      for (i32 j=0; j<C; j++)
        res[i][j] = A[i][j] * o;

    return res;
  }

  Matrix operator*(const Matrix &o) const {
    assert(C == o.R);
    
    Matrix res(R, o.C);
    for (i32 i=0; i<res.R; i++)
      for (i32 j=0; j<res.C; j++)
        for (i32 k=0; k<C; k++)
          res[i][j] += A[i][k] * o[k][j];

    return res;
  }

  Matrix pow(const Matrix &m, i64 power) const {
    if (power == 0) {
      Matrix res(m.R, m.C);
      for (i32 i=0; i<res.R; i++) res[i][i] = 1;
      return res;
    }

    auto h = pow(m, power/2);
    if (power&1) return h*h*m;
    else return h*h;
  }

  T det() const {
    assert(R == C);
    
    Matrix m(*this);
    T res = 1;
    for (i32 i=0; i<R; i++) {
      i32 pivot = -1;
      for (i32 j=i; j<R; j++) {
        if (m[j][i] != 0) {
          pivot = j;
          break;
        }
      }

      if (pivot == -1) return 0;
      if (pivot != i) {
        swap(m[i], m[pivot]);
        res = -res;
      }

      res *= m[i][i];
      T inv_pivot = m[i][i].inv();
      for (i32 j=i+1; j<R; j++) {
        T factor = m[j][i] * inv_pivot;
        for (i32 k=i; k<C; k++) {
          m[j][k] -= factor * m[i][k];
        }
      }
    }

    return res;
  }

  VT& operator[](i32 i) { return A[i]; }
  const VT& operator[](i32 i) const { return A[i]; }

  friend istream& operator>>(istream& is, Matrix& m) {
    for (i32 i=0; i<m.R; i++)
      for (i32 j=0; j<m.C; j++)
        is >> m[i][j];
    return is;
  }

  friend ostream& operator<<(ostream& os, const Matrix& m) {
    for (i32 i=0; i<m.R; i++) {
      for (i32 j=0; j<m.C; j++) {
        os << m[i][j] << (j == m.C - 1 ? "" : " ");
      }
      os << (i == m.R - 1 ? "" : "\n");
    }
    return os;
  }
};
