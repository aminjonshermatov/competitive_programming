//
// Created by aminjon on 11/5/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

auto solve() {
    ll N, M;
    cin >> N >> M;
    vector<tuple<ll, ll, ll>> A(2 * N + M);
    for (ll i = 0; i < N; ++i) {
        ll l, r;
        cin >> l >> r;
        A[2 * i] = make_tuple(l, 1, 2 * i);
        A[2 * i + 1] = make_tuple(r, -1, 2 * i + 1);
    }

    vector<ll> ans(M, 0);
    for (ll i = 0; i < M; ++i) {
        ll x;
        cin >> x;
        A[2 * N + i] = make_tuple(x, 0, i);
    }

    sort(A.begin(), A.end(), [](auto &l, auto &r) {
        return get<0>(l) < get<0>(r) || (get<0>(l) == get<0>(r) && get<1>(l) > get<1>(r));
    });
    ll cur = 0;
    for (auto [x, v, i] : A) {
        cur += v;
        if (v == 0) ans[i] = cur;
    }

    for (auto x : ans) cout << x << ' ';
}

int main() {
    solve();
}