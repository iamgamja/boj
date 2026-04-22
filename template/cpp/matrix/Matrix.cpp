#include <../default.hpp>

template <typename T>
struct Matrix {
  using VT = vector<T>;
  using VVT = vector<VT>;

  i32 R, C;
  VVT A;

  Matrix(i32 N): R(N), C(N), A(VVT(N, VT(N))) {};
  Matrix(i32 R, i32 C): R(R), C(C), A(VVT(R, VT(C))) {};
  Matrix(VVT A): A(A), R(A.size()), C(A[0].size()) {};

  Matrix operator*(const Matrix &o) const {
    assert(C == o.R);
    
    Matrix res(R, o.C);
    for (i32 i=0; i<res.R; i++)
      for (i32 j=0; j<res.C; j++)
        for (i32 k=0; k<C; k++)
          res[i][j] = res[i][j] + A[i][k] * o[k][j];

    return res;
  }
  VT& operator[](i32 i) { return A[i]; }
  const VT& operator[](i32 i) const { return A[i]; }
};
