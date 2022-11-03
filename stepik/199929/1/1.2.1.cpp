//
// Created by aminjon on 11/3/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

auto solve() {
    ll N, M;
    cin >> N >> M;

    vector<vector<ll>> A(N, vector<ll>(M));
    for (auto &r : A) for (auto &a : r) cin >> a;

    vector<vector<ll>> pf(N + 1, vector<ll>(M + 1, 0));
    for (ll i = 1; i <= N; ++i) {
        for (ll j = 1; j <= M; ++j) {
            pf[i][j] = A[i - 1][j - 1] + pf[i - 1][j] + pf[i][j - 1] - pf[i - 1][j - 1];
        }
    }

    ll Q;
    cin >> Q;
    for (ll _ = 0; _ < Q; ++_) {
        ll x1, y1, x2, y2;
        cin >> y1 >> x1 >> y2 >> x2;

        cout << pf[y2][x2] - pf[y1 - 1][x2] - pf[y2][x1 - 1] + pf[y1 - 1][x1 - 1] << '\n';
    }
}

int main() {
    solve();
}