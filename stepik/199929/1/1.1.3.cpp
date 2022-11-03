//
// Created by aminjon on 11/3/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

auto solve() {
    ll N;
    cin >> N;

    vector<ll> A(N);
    for (auto &a : A) cin >> a;

    ll st = 0, cur = 0;
    tuple<ll, ll, ll> ans;
    for (ll i = 0; i < N; ++i) {
        cur += A[i];
        if (cur > get<2>(ans)) ans = {st,i,cur};
        if (cur < 0) {
            cur = 0;
            st = i + 1;
        }
    }

    cout << get<0>(ans) + 1 << ' ' << get<1>(ans) + 1 << ' ' << get<2>(ans);
}

int main() {
    solve();
}