//
// Created by aminjon on 11/3/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

inline constexpr ll inf = numeric_limits<ll>::max();

auto solve() {
    ll N;
    cin >> N;

    vector<vector<ll>> dist(N, vector<ll>(N, inf));
    for (ll i = 0; i < N; ++i) {
        for (ll j = 0; j < N; ++j) {
            ll x;
            cin >> x;
            if (x != -1) dist[i][j] = x;
        }
    }

    for (ll k = 0; k < N; ++k) {
        for (ll i = 0; i < N; ++i) {
            for (ll j = 0; j < N; ++j) {
                if (dist[i][k] != inf && dist[k][j] != inf && i != j)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    ll dim = 0, ex = inf;
    for (ll i = 0; i < N; ++i) {
        ll local_ex = 0;
        for (ll j = 0; j < N; ++j) {
            if (dist[i][j] != inf) dim = max(dim, dist[i][j]), local_ex = max(local_ex, dist[i][j]);
        }
        ex = min(ex, local_ex);
    }
    cout << dim << '\n' << ex;
}

int main() {
    solve();
}