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

    tuple<ll, ll, ll> ans{0, 0, A[0]};
    for (ll l = 0, r = 0, cur = 0; r < N; ++r) {
        cur += A[r];
        if (cur < A[r]) l = r, cur = A[r];
        if (cur > get<2>(ans) || (cur == get<2>(ans) && r - l > get<1>(ans) - get<0>(ans))) ans = {l + 1, r + 1, cur};
    }

    cout << get<2>(ans) << '\n' << get<0>(ans) << ' ' << get<1>(ans);
}

int main() {
    solve();
}