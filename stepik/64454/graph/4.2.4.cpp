//
// Created by aminjon on 8/29/22.
//

#include "bits/stdc++.h"

using namespace std;

unordered_map<int, map<int, int>> adj;
vector<bool> seen;
vector<int> res;
int N, M;

void dfs(int n) {
    seen[n] = true;

    for (auto o : adj[n]) {
        if (!seen[o.first]) {
            res.push_back(o.second);
            dfs(o.first);
        }
    }
}

auto main() -> int32_t {
    cin >> N >> M;
    seen.assign(N + 1, false);

    for (int i = 0; i < M; ++i) {
        int p, q; cin >> p >> q;

        adj[p].emplace(q, i + 1);
        adj[q].emplace(p, i + 1);
    }

    dfs(1);
    cout << res.size() << '\n';
    for (auto n : res) cout << n << ' ';
}