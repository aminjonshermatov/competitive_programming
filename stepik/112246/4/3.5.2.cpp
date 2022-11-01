//
// Created by aminjon on 11/1/22.
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
            cin >> dist[i][j];
        }
    }

    ll mx = 0;
    for (ll k = 0; k < N; ++k) {
        for (ll i = 0; i < N; ++i) {
            for (ll j = 0; j < N; ++j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                mx = max(mx, dist[i][j]);
            }
        }
    }

    cout << mx;
}

int main() {
    solve();
}