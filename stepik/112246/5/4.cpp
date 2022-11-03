//
// Created by aminjon on 11/3/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

inline constexpr ll inf = numeric_limits<ll>::max();

auto solve() {
    ll N, M;
    cin >> N >> M;

    vector<vector<ll>> dist(N, vector<ll>(N, inf));
    for (ll i = 0; i < M; ++i) {
        ll s, e, l;
        cin >> s >> e >> l;
        --s, --e;
        dist[s][e] = dist[e][s] = l;
    }

    for (ll k = 0; k < N; ++k) {
        for (ll i = 0; i < N; ++i) {
            for (ll j = 0; j < N; ++j) {
                if (dist[i][k] != inf && dist[k][j] != inf && i != j) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    ll mx = 0;
    for (ll i = 0; i < N; ++i) {
        for (ll j = 0; j < N; ++j) if (dist[i][j] != inf) mx = max(mx, dist[i][j]);
    }
    cout << mx;
}

int main() {
    solve();
}