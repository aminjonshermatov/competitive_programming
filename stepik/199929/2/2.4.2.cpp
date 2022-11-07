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
    vector<pll> A(N);
    for (ll i = 0; i < N; ++i) {
        ll l, t;
        cin >> l >> t;
        A[i] = make_pair(l, t);
    }

    sort(A.begin(), A.end(), [](pll &l, pll &r) {
        return l.first < r.first || (l.first == r.first && l.second < r.second);
    });

    ll ans = 0;
    for (ll i = 0; i < N; ++i) {
        ll end = A[i].first + A[i].second;
        while (i + 1 < N && A[i + 1].first < end) ++i;
        ++ans;
    }

    cout << ans;
}

int main() {
    solve();
}