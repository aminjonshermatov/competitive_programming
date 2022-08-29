//
// Created by aminjon on 8/29/22.
//

#include "bits/stdc++.h"

using namespace std;

const int MAX_N = 1e2 + 1;

int adj[MAX_N][MAX_N];
int seen[MAX_N];
vector<int> res;
int N, M;

auto dfs(int n) -> void {
    seen[n] = 1;
    res.push_back(n + 1);
    for (int i = 0; i < N; ++i) {
        if (adj[n][i] && seen[i] == 0) {
            dfs(i);
            res.push_back(n + 1);
        }
    }
}

auto main() -> int32_t {
    cin >> N >> M;

    memset(adj, 0, sizeof(int) * N * N);
    memset(seen, 0, sizeof(int) * N);
    for (int i = 0; i < M; ++i) {
        int p, q; cin >> p >> q;
        --p, --q;
        adj[p][q] = adj[q][p] = 1;
    }

    int v; cin >> v;
    dfs(--v);

    cout << res.size() << '\n';
    for (auto n : res) cout << n << ' ';
    cout << '\n';
}