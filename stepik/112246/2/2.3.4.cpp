//
// Created by aminjon on 10/12/22.
//
#include <bits/stdc++.h>

using namespace std;

auto solve() {
    int N, M, K, C;
    cin >> N >> M >> K >> C;

    vector<bool> isC(N + 1, false);
    for (int i = 0; i < K; ++i) {
        int c;
        cin >> c;
        isC[c] = true;
    }

    vector<vector<pair<int, int>>> G(N + 1);
    for (int i = 0; i < M; ++i) {
        int s, e, t;
        cin >> s >> e >> t;
        G[s].emplace_back(e, t);
        G[e].emplace_back(s, t);
    }

    vector<int> dist(N + 1, INT_MAX);
    dist[C] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({C, 0});
    while (!pq.empty()) {
        auto [v, vt] = pq.top(); pq.pop();

        for (auto [u, ut] : G[v]) {
            if (vt + ut < dist[u]) {
                dist[u] = vt + ut;
                pq.push({u, dist[u]});
            }
        }
    }

    vector<int> res;
    res.reserve(K);
    for (int i = 1; i <= N; ++i) {
        if (isC[i]) res.emplace_back(dist[i]);
    }
    sort(res.begin(), res.end());
    for (int i = 0; i < K; ++i) cout << i + 1 << ' ' << res[i] << '\n';
}

int main() {
    solve();
}