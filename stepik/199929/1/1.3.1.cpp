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

    vector<ll> pf_max(N + 1, 0), sf_max(N + 1, 0);
    for (ll i = K; i <= N; ++i) pf_max[i] = max(pf_max[i - 1], pf[i] - pf[i - K]);
    for (ll i = N - K + 1; i >= K; --i) sf_max[i] = max(sf_max[i + 1], pf[i + K - 1] - pf[i - 1]);

    ll ans = 0;
    for (ll i = K; i + K - 1 <= N; ++i) ans = max(ans, min(pf_max[i - 1], sf_max[i + K - 1]));
    cout << ans;
}

int main() {
    solve();
}