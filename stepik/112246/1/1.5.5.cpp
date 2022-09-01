//
// Created by aminjon on 9/1/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t N = 1e5 + 1;
set<int> G[N];
int seen[N], u, v, next_[N];
bool found = false;

auto dfs(int from) -> void {
    seen[from] = 1;

    for (auto to : G[from]) {
        if (found) return;
        if (to == v) {
            next_[from] = to;
            found = true;
            return;
        }
        if (!seen[to]) {
            next_[from] = to;
            dfs(to);
        }
    }
}

auto main() -> int32_t {
    int n, m; cin >> n >> m;

    memset(seen, 0, sizeof(int) * n);
    memset(next_, -1, sizeof(int) * n);
    for (int i = 0; i < m; ++i) {
        int p, q; cin >> p >> q;
        G[--p].insert(--q);
        G[q].insert(p);
    }

    cin >> u >> v;
    --u, --v;
    if (u == v) {
        cout << u << '\n';
        return 0;
    }

    dfs(u);
    if (!found) {
        cout << "no solution" << '\n';
        return 0;
    }

    for (int i = u; i < n && i != -1; i = next_[i]) cout << i  + 1 << ' ';
}