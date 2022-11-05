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

    pair<ll, ll> ans = {0, 0};
    map<ll, ll> cnt{};
    ll cur = 0;
    for (ll l = 0, r = 0; r < N; ++r) {
        cur += ++cnt[A[r]] == 1;
        while (l < r && cur > K) cur -= --cnt[A[l++]] == 0;
        if (ans.second - ans.first <= r - l) ans = {l + 1, r + 1};
    }

    cout << ans.first << ' ' << ans.second;
}

int main() {
    solve();
}