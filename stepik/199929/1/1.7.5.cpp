//
// Created by aminjon on 11/5/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

auto solve() {
    ll N, K;
    cin >> N >> K;

    vector<ll> A(N);
    for (auto &a : A) cin >> a;

    for (ll l = 0, r = 0, s = 0; r < N; ++r) {
        s += A[r];
        while (l < r && s > K) s -= A[l++];
        if (s == K) { cout << l + 1 << ' ' << r + 1; return; }
    }
}

int main() {
    solve();
}