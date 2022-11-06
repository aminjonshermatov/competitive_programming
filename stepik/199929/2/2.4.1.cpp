//
// Created by aminjon on 11/7/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

auto solve() {
    ll N;
    cin >> N;

    vector<pll> A;
    A.reserve(2 * N);
    for (ll i = 0; i < N; ++i) {
        ll l, r;
        cin >> l >> r;
        A.emplace_back(l, 1);
        A.emplace_back(r, -1);
    }

    sort(A.begin(), A.end(), [](pll &l, pll &r) {
        return l.first < r.first || (l.first == r.first && l.second > r.second);
    });

    ll open = 0;
    for (auto [x, t] : A) {
        open += t;
        if (open > 2) { cout << "NO"; return; }
    }

    cout << "YES";
}

int main() {
    solve();
}