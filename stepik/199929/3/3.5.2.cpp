//
// Created by aminjon on 11/8/22.
//
#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

inline constexpr int inf = numeric_limits<int>::max();

auto solve() {
    int N;
    cin >> N;

    vector<int> cost(N);
    for (auto &c : cost) cin >> c;

    int M;
    cin >> M;
    vector<vector<int>> g(N);
    for (int i = 0; i < M; ++i) {
        int p, q;
        cin >> p >> q;
        --p, --q;
        g[p].emplace_back(q);
        g[q].emplace_back(p);
    }

    vector<int> dist(N, inf);
    priority_queue<pii, vector<pii>, greater<>> pq;

    pq.emplace(0, 0);

    while (!pq.empty()) {
        auto [c, v] = pq.top(); pq.pop();

        for (auto u : g[v]) {
            if (c + cost[v] < dist[u]) {
                dist[u] = c + cost[v];
                pq.emplace(dist[u], u);
            }
        }
    }

    cout << (dist[N - 1] == inf ? -1 : dist[N - 1]);
}

int main() {
    solve();
}