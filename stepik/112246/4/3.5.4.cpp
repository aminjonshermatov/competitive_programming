//
// Created by aminjon on 11/1/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

inline constexpr ll inf = numeric_limits<ll>::max();

inline constexpr array<ll, 5> dk = {1, 0, -1, 0, 1};

auto solve() {
    ll N, M;
    cin >> N >> M;

    auto is_safe = [&](ll i, ll j) { return i >= 0 && i < N && j >= 0 && j < M; };

    vector<string> adj(N);
    pll start;
    for (ll i = 0; i < N; ++i) {
        cin >> adj[i];
        if (auto pos = adj[i].find('*'); pos != string::npos) start = {i, pos};
    }

    vector<vector<ll>> dist(N, vector<ll>(M, inf));
    dist[start.first][start.second] = 0;
    queue<pll> q;
    q.emplace(start);

    while (!q.empty()) {
        auto [i, j] = q.front(); q.pop();

        for (ll k = 0; k < 4; ++k) {
            ll ii = i + dk[k], jj = j + dk[k + 1];

            if (is_safe(ii, jj) && adj[ii][jj] == '0') {
                dist[ii][jj] = dist[i][j] + 1;
                adj[ii][jj] = '1';
                q.emplace(ii, jj);
            }
        }
    }

    ll K;
    cin >> K;
    pll ans = {inf, -1};
    for (ll k = 1; k <= K; ++k) {
        ll i, j;
        cin >> i >> j;
        if (dist[--i][--j] < ans.first) ans.first = dist[i][j], ans.second = k;
    }

    cout << ans.second;
}

int main() {
    solve();
}