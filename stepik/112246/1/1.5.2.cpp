//
// Created by aminjon on 9/1/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t N = 1e5 + 1;
vector<int> G[N];
int C[N];

auto dfs(int v, int c) -> int {
    C[v] = c;

    for (auto to : G[v]) {
        if (C[to] != c) dfs(to, c);
    }
}

auto main() -> int32_t {
    int n, m; cin >> n >> m;

    fill(C, C + n, N);
    for (int i = 0; i < m; ++i) {
        int p, q; cin >> p >> q;
        --p; --q;
        G[p].push_back(q);
        G[q].push_back(p);
    }

    int c = 0;
    for (int i = 0; i < n; ++i) {
        if (C[i] > c) dfs(i, c++);
    }

    vector<vector<int>> res(c);
    for (int i = 0; i < n; ++i) res[C[i]].push_back(i + 1);

    cout << c << '\n';
    for (int i = 0; i < c; ++i) {
        cout << res[i].size() << '\n';
        for (auto it : res[i]) cout << it << ' ';
        cout << '\n';
    }
}