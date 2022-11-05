//
// Created by aminjon on 11/5/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

auto solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    for (auto &a : A) cin >> a;

    tuple<ll, ll, ll> ans{-1, -1, -10001};
    ll cur = 0, l = 0;
    for (ll r = 0; r < N; ++r) {
        cur += A[r];
        if (cur > get<2>(ans)) ans = {l + 1, r + 1, cur};
        if (cur < 0) cur = 0, l = r + 1;
    }

    cout << get<0>(ans) << ' ' << get<1>(ans) << ' ' << get<2>(ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}