//
// Created by aminjon on 10/26/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

inline constexpr auto inf = numeric_limits<ll>::max();

auto solve() {
    ll N, S, F, M;
    cin >> N >> S >> F >> M;

    vector<vector<array<ll, 3>>> G(N + 1);
    for (ll i = 0; i < M; ++i) {
        ll s, st, e, et;
        cin >> s >> st >> e >> et;
        G[s].push_back({st, e, et});
    }

    vector<ll> dist(N + 1, inf);
    queue<pll> q;

    q.push({S, 0});
    dist[S] = 0;

    while (!q.empty()) {
        auto [v, t] = q.front(); q.pop();

        for (auto &it : G[v]) {
            ll vt = it[0], u = it[1], ut = it[2];

            if (t <= vt && ut < dist[u]) {
                dist[u] = ut;
                q.push({u, ut});
            }
        }
    }

    cout << dist[F];
}

int main() {
    solve();
}