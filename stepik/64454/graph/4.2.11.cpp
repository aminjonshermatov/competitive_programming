//
// Created by aminjon on 8/31/22.
//
#include "bits/stdc++.h"

using namespace std;

const int MAX_N = 1e5 + 1;
vector<int> G[MAX_N];
vector<int> W, T;

auto main() -> int32_t {
    int n, m; cin >> n >> m;

    W.assign(n + 1, 0);
    T.resize(n, 0);
    for (int i = 0; i < m; ++i) {
        int p, q; cin >> p >> q;

        ++W[p];
        G[q].emplace_back(p);
    }

    for (int i = 0; i < m; ++i) cin >> T[i];
    int c = 0, v;
    for (int i = 1; i <= n; ++i) {
        if (W[i] == 0) {
            ++c;
            v = i;
        }
    }

    while (c == 1) {
        c = 0;
        auto &it = G[v];
        for (auto u : it) {
            if (--W[u] == 0) {
                ++c;
                v = u;
            }
        }
    }

    cout << (c == 0 ? "YES" : "NO") << '\n';
}