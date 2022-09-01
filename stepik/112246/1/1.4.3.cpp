//
// Created by aminjon on 9/1/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t N = 101u;
int G[N][N];

auto main() -> int32_t {
    int n, m; cin >> n >> m;

    memset(G, 0, sizeof(int) * n * n);
    for (int i = 0; i < m; ++i) {
        int p, q; cin >> p >> q;
        G[--p][--q] = 1;
    }

    bool ok = true;
    for (int i = 0; i < n && ok; ++i) {
        for (int j = 0; j < n && ok; ++j) {
            ok = i == j || G[i][j] + G[j][i] == 1;
        }
    }

    cout << (ok ? "YES" : "NO");
}