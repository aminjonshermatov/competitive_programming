//
// Created by aminjon on 10/31/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

inline constexpr ll neg = 100000;
inline constexpr ll inf = numeric_limits<ll>::max();

auto solve() {
    ll N;
    cin >> N;

    vector<vector<pll>> G(N);
    for (ll i = 0; i < N; ++i) {
        for (ll j = 0; j < N; ++j) {
            ll w;
            cin >> w;
            if (w != neg) G[i].emplace_back(j, w);
        }
    }

    vector<ll> dist(N), p(N);

    for (ll s = 0; s < N; ++s) {
        fill(dist.begin(), dist.end(), inf);
        fill(p.begin(), p.end(), -1);

        dist[s] = 0;
        ll x = -1;
        for (ll k = 0; k < N; ++k) {
            x = -1;
            for (ll v = 0; v < N; ++v) {
                for (auto [u, w] : G[v]) {
                    if (dist[v] != inf && dist[v] + w < dist[u]) {
                        x = u;
                        p[u] = v;
                        dist[u] = dist[v] + w;
                    }
                }
            }

            if (k + 1 == N && x != -1) {
                cout << "YES";
                return;
            }
        }
    }

    cout << "NO";
}

int main() {
    solve();
}