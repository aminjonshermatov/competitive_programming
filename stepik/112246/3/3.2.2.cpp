//
// Created by aminjon on 10/26/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

inline constexpr auto inf = numeric_limits<ll>::max();

auto solve() {
    ll N, M, K, S, F;
    cin >> N >> M >> K >> S >> F;

    vector<vector<pll>> G(N + 1);
    for (ll i = 0; i < M; ++i) {
        ll s, f, p;
        cin >> s >> f >> p;
        G[s].emplace_back(f, p);
    }

    vector<vector<ll>> cost(N + 1, vector<ll>(K + 1, inf));
    vector<vector<bool>> used(N + 1, vector<bool>(K + 1, false));
    queue<pll> q;

    q.push({S, 0});
    cost[S][0] = 0;
    used[S][0] = true;

    while (!q.empty()) {
        auto [v, d] = q.front(); q.pop();
        used[v][d] = false;

        for (auto [u, p] : G[v]) {
            if (d + 1 <= K && cost[v][d] + p < cost[u][d + 1]) {
                cost[u][d + 1] = cost[v][d] + p;
                if (!used[u][d + 1]) {
                    q.push({u, d + 1});
                    used[u][d + 1] = true;
                }
            }
        }
    }

    ll min_c = inf;
    for (ll d = 0; d <= K; ++d) min_c = min(min_c, cost[F][d]);

    cout << (min_c == inf ? -1 : min_c);
}

int main() {
    solve();
}
