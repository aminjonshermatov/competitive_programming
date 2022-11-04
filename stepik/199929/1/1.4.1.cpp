//
// Created by aminjon on 11/4/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

auto solve() {
    ll N, K;
    cin >> N >> K;

    vector<ll> pf(N + 1, 0);
    for (ll i = 1; i <= N; ++i) {
        ll x;
        cin >> x;
        pf[i] = pf[i - 1] + x;
    }

    ll ans = 0;
    for (ll i = 1; i <= N; ++i) {
        ans += N - (lower_bound(pf.begin(), pf.end(), pf[i - 1] + K) - pf.begin()) + 1;
    }
    cout << ans;
}

int main() {
    solve();
}