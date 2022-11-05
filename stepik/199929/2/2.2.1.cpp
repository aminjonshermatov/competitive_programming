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
    vector<pll> A(2 * N);
    for (ll i = 0; i < N; ++i) {
        ll l, r;
        cin >> l >> r;
        A[2 * i] = make_pair(l, 1);
        A[2 * i + 1] = make_pair(r, -1);
    }

    sort(A.begin(), A.end(), [](pll &l, pll &r) {
        return l.first < r.first || (l.first == r.first && l.second > r.second);
    });
    ll cur = 0, ans = 0, l;
    for (auto [x, v] : A) {
        if (cur == 0) l = x;
        cur += v;
        if (cur == 0) ans += x - l;
    }

    cout << ans;
}

int main() {
    solve();
}