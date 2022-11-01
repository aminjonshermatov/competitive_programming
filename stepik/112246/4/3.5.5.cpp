//
// Created by aminjon on 11/1/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

inline constexpr ll inf = numeric_limits<ll>::max();

auto solve() {
    ll N, M;
    cin >> N >> M;

    vector<vector<ll>> dist(N, vector<ll>(N, inf));
    for (ll i = 0; i < N; ++i) dist[i][i] = 0;

    for (ll i = 0; i < M; ++i) {
        ll s, e, w;
        cin >> s >> e >> w;
        --s, --e;

        dist[s][e] = dist[e][s] = w;
    }

    for (ll k = 0; k < N; ++k) {
        for (ll i = 0; i < N; ++i) {
            for (ll j = 0; j < N; ++j) {
                if (dist[i][k] != inf && dist[k][j] != inf)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    if (M == 0) { cout << 1; return; }

    pll ans = {inf, -1};
    for (ll i = 0; i < N; ++i) {
        ll mx = 0;
        for (ll j = 0; j < N; ++j) mx = max(mx, dist[i][j]);
        if (mx < ans.first) ans = {mx, i + 1};
    }

    cout << ans.second;
}

int main() {
    solve();
}