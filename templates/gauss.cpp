//
// Created by aminjon on 3/9/23.
//
#include <bits/stdc++.h>

using ld = long double;

vector<ld> gauss(vector<vector<ld>> &A) {
    const int n(A.size());
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
                swap(A[i][j], A[i2][j]);
            }
        }

        assert(A[i][i] != 0);
        for (int i2 = i + 1; i2 < n; ++i2) {
            if (A[i2][i] == 0) continue ;
            auto coeff = A[i][i] / A[i2][i];
            for (int j = 0; j <= n; ++j) {
                A[i2][j] = A[i][j] - coeff * A[i2][j];
            }
        }
    }

    vector<ld> X(n);
    for (int i = n - 1; i >= 0; --i) {
        ld sm = A[i][n];
        for (int j = i + 1; j < n; ++j) {
            sm -= X[j] * A[i][j];
        }
        X[i] = sm / A[i][i];
    }
    return X;
}