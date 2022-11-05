//
// Created by aminjon on 11/5/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

auto solve() {
    ll N, ans = 0;
    cin >> N;
    for (ll i = 0; i < N; ++i) {
        ll x;
        cin >> x;
        ans ^= x;
    }

    cout << ans;
}

int main() {
    solve();
}