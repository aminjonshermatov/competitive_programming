//
// Created by aminjon on 11/1/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

auto solve() {
    ll N;
    cin >> N;

    vector<vector<ll>> G(N);
    for (ll i = 0; i < N; ++i) {
        for (ll j = 0; j < N; ++j) {
            ll x;
            cin >> x;

            if (x != 0) G[i].emplace_back(j);
        }
    }

    vector<ll> used(N, 0);
    auto dfs = [&](auto &self, ll v) -> bool {
        used[v] = 1;
        for (auto u : G[v]) if (used[u] == 1 || (used[u] == 0 && self(self, u)))  return true;
        used[v] = 2;
        return false;
    };

    for (ll i = 0; i < N; ++i) {
        if (used[i] == 0 && dfs(dfs, i)) { cout << 1; return; }
    }

    cout << 0;
}

int main() {
    solve();
}