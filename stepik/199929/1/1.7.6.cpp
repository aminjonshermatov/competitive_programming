//
// Created by aminjon on 11/5/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

auto solve() {
    ll N, s = 0;
    cin >> N;

    for (ll i = 0; i < N - 1; ++i) {
        ll x;
        cin >> x;
        s += x;
    }

    cout << N * (N + 1) / 2 - s;
}

int main() {
    solve();
}