//
// Created by aminjon on 10/26/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

inline constexpr auto inf = numeric_limits<ll>::max();

auto solve() {
    ll N, M, S = 1;
    cin >> N >> M;

    vector<vector<pair<ll, ll>>> G(N + 1);
    for (ll i = 0; i < M; ++i) {
        ll u, v, w;
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
    }

    vector<ll> dist(N + 1, inf), p(N + 1, -1);
    vector<bool> used(N + 1, false);

    queue<ll> q;
    q.push(S);
    dist[S] = 0;
    used[S] = true;

    while (!q.empty()) {
        auto v = q.front(); q.pop();
        used[v] = false;

        for (auto [u, w] : G[v]) {
            if (dist[v] + w < dist[u]) {
                dist[u] = dist[v] + w;
                p[u] = v;
                if (!used[u]) q.push(u);
            }
        }
    }

    for (ll v = 1; v <= N; ++v) {
        cout << (dist[v] == inf ? 30'000 : dist[v]) << ' ';
    }
    cout << '\n';
}

int main() {
    solve();
}