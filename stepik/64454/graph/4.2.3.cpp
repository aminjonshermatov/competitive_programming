//
// Created by aminjon on 8/29/22.
//

#include "bits/stdc++.h"

using namespace std;

unordered_map<int, set<int>> adj;
vector<int> L;
int N, M, ans = 0;

void dfs(int n, int v) {
    L[n] = v;

    for (auto o : adj[n]) {
        if (L[o] == -1) dfs(o, v + 1);
        else if (L[o] > v) ++ans;
    }
}

auto main() -> int32_t {
    cin >> N >> M;
    L.assign(N + 1, -1);

    for (int i = 0; i < M; ++i) {
        int p, q; cin >> p >> q;

        adj[p].insert(q);
        adj[q].insert(p);
    }

    dfs(1, 1);
    cout << ans << '\n';
}