//
// Created by aminjon on 3/9/23.
//
#include <bits/stdc++.h>

// A_{1,1}*X_{1,1}+...+A_{1,n}*X_{1,n}=A_{1,n+1}
// ...
// A_{n,1}*X_{n,1}+...+A_{n,n}*X_{n,n}=A_{n,n+1}

std::vector<long double> gauss(std::vector<std::vector<long double>> &A) {
  const auto n = int(A.size());
  for (int i = 0; i < n; ++i) {
    if (A[i][i] == 0) {
      int i2 = -1;
      for (int j = i + 1; j < n; ++j) {
        if (A[i][j] != 0) {
          i2 = j;
          break;
        }
      }
      assert(i2 != -1);
      for (int j = 0; j <= n; ++j) {
        std::swap(A[i][j], A[i2][j]);
      }
    }

    assert(A[i][i] != 0);
    for (int i2 = i + 1; i2 < n; ++i2) {
      if (A[i2][i] == 0) continue ;
      auto c = A[i][i] / A[i2][i];
      for (int j = 0; j <= n; ++j) {
        A[i2][j] = A[i][j] - c * A[i2][j];
      }
    }
  }

  std::vector<long double> X(n);
  for (int i = n - 1; i >= 0; --i) {
    long double sm = A[i][n];
    for (int j = i + 1; j < n; ++j) {
      sm -= X[j] * A[i][j];
    }
    X[i] = sm / A[i][i];
  }
  return X;
}