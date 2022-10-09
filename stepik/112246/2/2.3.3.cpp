//
// Created by aminjon on 10/9/22.
//
#include "bits/stdc++.h"

using namespace std;

using ll = long long;

const ll inf = 1e15;

auto solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<ll, ll>>> G(n);
    for (int i = 0; i < m; ++i) {
        int p, q, w;
        cin >> p >> q >> w;
        G[p].emplace_back(q, w);
        G[q].emplace_back(p, w);
    }

    ll s;
    cin >> s;
    const ll def_ = 2009000999;
    vector<ll> dist(n, def_);
    vector<ll> p(n);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    dist[s] = 0;
    p[s] = -1;
    pq.emplace(0, s);

    while (!pq.empty()) {
        auto [d, v] = pq.top(); pq.pop();
        if (d > dist[v]) continue;

        for (const auto [u, ud] : G[v]) {
            if (d + ud < dist[u]) {
                dist[u] = d + ud;
                p[u] = v;
                pq.emplace(dist[u], u);
            }
        }
    }

    for (auto d : dist) cout << d << ' ';
    cout << '\n';
}

auto main() -> int32_t {
    ll t; cin >> t;
    while (t--) solve();
}