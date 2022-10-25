//
// Created by aminjon on 10/25/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

inline constexpr ll inf = numeric_limits<ll>::max();

auto solve() {
    ll N, K;
    cin >> N >> K;

    vector<vector<array<ll, 3>>> G(N + 1);
    for (ll i = 0; i < K; ++i) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        G[a].push_back({b, c, d});
    }

    ll M, prev; cin >> M >> prev;
    vector<ll> P(M - 1), dist(N + 1);
    for (auto &p : P) cin >> p;

    ll ans = 0;
    priority_queue<pll, vector<pll>, greater<>> pq;
    for (auto p : P) {
        fill(dist.begin(), dist.end(), inf);
        dist[prev] = ans;

        pq.push({ans, prev});
        while (!pq.empty()) {
            auto [t, v] = pq.top(); pq.pop();

            for (auto u : G[v]) {
                auto st = t + (u[1] - t % u[1]) % u[1];
                if (t <= st && st + u[2] < dist[u[0]]) {
                    dist[u[0]] = st + u[2];
                    pq.push({dist[u[0]], u[0]});
                }
            }
        }

        if (dist[p] == inf) {
            cout << -1;
            return;
        }

        ans = dist[p];
        prev = p;
    }

    cout << ans;
}

int main() {
    solve();
}