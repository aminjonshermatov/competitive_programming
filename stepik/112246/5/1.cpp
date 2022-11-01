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

    vector<ll> dist(N, inf), p(N, -1);
    vector<bool> used(N, false);
    dist[0] = 0;
    used[0] = true;
    queue<ll> q;
    q.emplace(0);

    while (!q.empty()) {
        auto v = q.front(); q.pop();
        used[v] = false;

        for (ll u = v + 1; u < N; ++u) {
            ll w = (179 * (v + 1) + 719 * (u + 1)) % 1000 - 500;
            if (dist[v] + w < dist[u]) {
                dist[u] = dist[v] + w;
                p[u] = v;

                if (!used[u]) {
                    used[u] = true;
                    q.emplace(u);
                }
            }
        }
    }

    cout << dist[N - 1];
}

int main() {
    solve();
}