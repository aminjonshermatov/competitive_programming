//
// Created by aminjon on 11/2/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

inline constexpr ll inf = numeric_limits<ll>::max();

auto solve() {
    ll N;
    cin >> N;

    vector<vector<ll>> dist(N, vector<ll>(N, inf));
    for (ll i = 0; i < N; ++i) {
        for (ll j = 0; j < N; ++j) {
            ll x;
            cin >> x;
            if (x != 0) dist[i][j] = x;
        }
    }

    vector<vector<pll>> prev(N, vector<pll>(N, {-1, -1}));
    for (ll k = 0; k < N; ++k) {
        for (ll i = 0; i < N; ++i) {
            for (ll j = 0; j < N; ++j) {
                if (dist[i][k] != inf && dist[k][j] != inf) {
                    if (dist[i][k] + dist[k][k] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        prev[i][j] = {k, j};
                    }
                }
            }
        }
    }

    for (ll i = 0; i < N; ++i) {
        for (ll j = 0; j < N; ++j) {
            set<pll> seen;
            set<ll> v;
            auto cur = pair{i, j};
            while (cur.first != -1) {
                seen.emplace(cur);
                v.insert(cur.first);
                v.insert(cur.second);
                cur = prev[cur.first][cur.second];
                if (seen.count(cur) > 0) break;
            }

            bool has_c = false;
            for (auto u: v) has_c |= dist[u][u] < 0;

            if (dist[i][j] == inf) cout << 0;
            else if (has_c) cout << 2;
            else cout << 1;
            cout << ' ';
        }
        cout << '\n';
    }
}

int main() {
    solve();
}