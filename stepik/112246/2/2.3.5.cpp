//
// Created by aminjon on 10/12/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

auto solve() {
    ll N, S, E, M;
    cin >> N >> S >> E >> M;

    vector<vector<array<ll, 3>>> G(N + 1);
    for (ll i = 0; i < M; ++i) {
        ll s, st, e, et;
        cin >> s >> st >> e >> et;

        G[s].push_back({st, e, et});
    }

    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;
    vector<ll> dist(N + 1, numeric_limits<ll>::max());
    dist[S] = 0;
    pq.push({0, S});

    while (!pq.empty()) {
        auto [t, v] = pq.top(); pq.pop();

        for (auto it : G[v]) {
            auto st = it[0], e = it[1], et = it[2];

            if (t <= st && et < dist[e]) {
                dist[e] = et;
                pq.push({et, e});
            }
        }
    }

    cout << (dist[E] == numeric_limits<ll>::max() ? -1 : dist[E]) << '\n';
}

int main() {
    solve();
}