//
// Created by aminjon on 11/1/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

inline constexpr ll inf = numeric_limits<ll>::max();

auto solve() {
    ll N, S, T;
    cin >> N >> S >> T;

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
                if (dist[i][k] != inf && dist[k][j] != inf) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    cout << (dist[--S][--T] == inf ? -1 : dist[S][T]);
}

int main() {
    solve();
}