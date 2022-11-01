//
// Created by aminjon on 11/1/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

inline constexpr ll inf = 1e12;

auto solve() {
    ll N, M;
    cin >> N >> M;

    vector<vector<pll>> G(N + 1);
    set<ll> cycle;
    for (ll i = 0; i < M; ++i) {
        ll a, b, w;
        cin >> a >> b >> w;

        if (a == b) cycle.insert(a);

        G[a].emplace_back(b, -w);
    }

    vector<ll> dist(N + 1, inf), p(N + 1, -1);
    dist[1] = 0;

    ll x;
    for (ll k = 0; k < N; ++k) {
        x = -1;

        for (ll a = 1; a <= N; ++a) {
            for (auto [b, w] : G[a]) {
                if (dist[a] != inf && dist[a] + w < dist[b]) {
                    x = b;
                    p[b] = a;
                    dist[b] = dist[a] + w;
                }
            }
        }

        if (k + 1 != N) x = -1;
    }


    vector<bool> used(N + 1, false);

    auto dfs = [&](auto &self, ll v) -> void {
        for (auto [u, _] : G[v]) if (!used[u]) {
                used[u] = true;
                self(self, u);
            }
    };

    if (x != -1) used[x] = true, dfs(dfs, x);

    bool ok = used[N];
    set<ll> seen;
    for (auto v = N; v != -1; v = p[v]) {
        ok |= used[v];
        if (cycle.count(v) > 0 || seen.count(v) > 0) { ok = true; x = 1; break; }
        seen.insert(v);
    }

    if (dist[N] == inf) cout << ":(";
    else if (x != -1 && ok) cout << ":)";
    else cout << -dist[N];
}

int main() {
    solve();
}
