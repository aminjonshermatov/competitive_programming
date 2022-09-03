//
// Created by aminjon on 9/3/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t N = 101u;
int G[N][N];

auto main() -> int32_t {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cin >> G[i][j];
    }

    int p, q; cin >> p >> q;
    --p, --q;

    vector<int> dist(n, -1), pred(n, -1);
    dist[p] = 0;
    queue<int> Q;
    Q.push(p);

    while (!Q.empty()) {
        auto v = Q.front(); Q.pop();

        for (int u = 0; u < n; ++u) {
            if (dist[u] == -1 && G[v][u] == 1) {
                dist[u] = dist[v] + 1;
                pred[u] = v;
                Q.push(u);
            }
        }
    }

    cout << dist[q] << '\n';
}