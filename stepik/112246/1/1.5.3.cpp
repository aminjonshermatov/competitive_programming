//
// Created by aminjon on 9/1/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t N = 1e5 + 1;
set<int> G[N];
int seen[N];
vector<int> res;

auto dfs(int v) -> int {
    seen[v] = 1;
    res.emplace_back(v + 1);

    for (auto to : G[v]) {
        if (seen[to] == -1) dfs(to);
    }
}

auto main() -> int32_t {
    int n, m; cin >> n >> m;

    memset(seen, -1, sizeof(int) * n);
    for (int i = 0; i < m; ++i) {
        int p, q; cin >> p >> q;
        --p; --q;
        if (p != q) G[q].insert(p);
    }

    dfs(0);
    sort(res.begin(), res.end());
    for (auto v : res) cout << v << ' ';
    cout << '\n';
}