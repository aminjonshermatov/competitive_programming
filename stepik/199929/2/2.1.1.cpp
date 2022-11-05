//
// Created by aminjon on 11/5/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

auto solve() {
    ll L, R, N;
    cin >> L >> R >> N;
    vector<pll> A;
    A.reserve(2 * N);
    for (ll i = 0; i < N; ++i) {
        ll l, r;
        cin >> l >> r;
        A.emplace_back(l, 1);
        A.emplace_back(r, -1);
    }

    sort(A.begin(), A.end(), [](pll &l, pll &r) {
        return l.first < r.first || (l.first == r.first && l.second == 1);
    });
    ll cur = 0;
    for (auto [x, v] : A) {
        cur += v;
        if (x >= L && x < R && cur <= 0) { cout << "NO"; return; }
    }

    cout << "YES";
}

int main() {
    solve();
}