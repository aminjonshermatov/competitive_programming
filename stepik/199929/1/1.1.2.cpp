//
// Created by aminjon on 11/3/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

auto solve() {
    ll N;
    cin >> N;

    vector<ll> pf(N + 1, 0);
    for (ll i = 1; i <= N; ++i) {
        ll x; cin >> x;
        pf[i] = pf[i - 1] + x;
    }

    ll M;
    cin >> M;
    for (ll i = 0; i < M; ++i) {
        ll l, r;
        cin >> l >> r;
        cout << pf[r] - pf[l - 1] << '\n';
    }
}

int main() {
    solve();
}