//
// Created by aminjon on 11/3/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

auto solve() {
    ll N;
    cin >> N;

    ll pref = 0;
    for (ll i = 0; i < N; ++i) {
        ll x; cin >> x;
        pref += x;
        cout << pref << ' ';
    }
}

int main() {
    solve();
}