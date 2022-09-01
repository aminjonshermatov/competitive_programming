
//
// Created by aminjon on 9/1/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t N = 1e5 + 1;
set<int> G[N];
int seen[N];

auto dfs(int v) -> int {
    seen[v] = 1;

    int ans = 1;
    for (auto to : G[v]) {
        if (!seen[to]) ans += dfs(to);
    }
    return ans;
}

auto main() -> int32_t {
    int n, m; cin >> n >> m;

    memset(seen, 0, sizeof(int) * n);
    for (int i = 0; i < m; ++i) {
        int p, q; cin >> p >> q;
        --p; --q;
        G[p].insert(q);
        G[q].insert(p);
    }

    cout << dfs(0) << '\n';
    for (int i = 0; i < n; ++i) if (seen[i] != 0) cout << i + 1 << ' ';
    cout << '\n';
}