
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
        --p, --q;
        ++G[min(p, q)][max(p, q)];
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (G[i][j] > 1) ++ans;
        }
    }

    cout << ans;
}