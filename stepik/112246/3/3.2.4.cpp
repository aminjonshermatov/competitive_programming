//
// Created by aminjon on 10/31/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

auto solve() {
    ll N, M, S;
    ld V;
    cin >> N >> M >> S >> V;

    vector<vector<tuple<ll, ld, ld>>> G(N + 1);
    for (ll i = 0; i < M; ++i) {
        ll a, b;
        ld rab, cab, rba, cba;
        cin >> a >> b >> rab >> cab >> rba >> cba;

        G[a].emplace_back(b, rab, cab);
        G[b].emplace_back(a, rba, cba);
    }

    vector<ld> profit(N + 1, 0);
    profit[S] = V;
    vector<ll> used(N + 1, false);
    used[S] = true;
    queue<pair<ll, ld>> q;
    q.emplace(S, V);
    while (!q.empty()) {
        auto [a, v] = q.front(); q.pop();
        used[a] = false;

        for (auto it : G[a]) {
            ll b = get<0>(it);
            ld r = get<1>(it), c = get<2>(it);

            auto can = (v - c) * r;
            if (can >= 0 && can > profit[b]) {
                profit[b] = can;
                if (!used[b]) {
                    q.emplace(b, can);
                    used[b] = true;
                }
            }
        }
    }

    bool ok = false;
    vector<ld> temp_profit(N + 1);
    for (ll A = 1; A <= N; ++A) {
        if (A == S) continue;

        fill(temp_profit.begin(), temp_profit.end(), 0);
        fill(used.begin(), used.end(), false);
        temp_profit[A] = profit[A];
        used[A] = true;
        q.emplace(A, profit[A]);
        while (!q.empty()) {
            auto [a, v] = q.front(); q.pop();
            used[a] = false;

            for (auto it : G[a]) {
                ll b = get<0>(it);
                ld r = get<1>(it), c = get<2>(it);

                auto can = (v - c) * r;
                if (can >= 0 && can > temp_profit[b]) {
                    temp_profit[b] = can;
                    if (!used[b]) {
                        q.emplace(b, can);
                        used[b] = true;
                    }
                }
            }
        }

        ok |= temp_profit[S] > V;
    }

    cout << (ok ? "YES" : "NO");
}

int main() {
    solve();
}