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

    ll M;
    cin >> M;
    vector<ll> B(M);
    for (auto &b : B) cin >> b;

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    ll ans = 0, l = 0;
    for (ll i = 0; i < N && l < M; ++i) {
        while (l < M && B[l] + 1 < A[i]) ++l;
        if (l < M && abs(A[i] - B[l]) <= 1) ++ans, ++l;
    }

    cout << ans;
}

int main() {
    solve();
}