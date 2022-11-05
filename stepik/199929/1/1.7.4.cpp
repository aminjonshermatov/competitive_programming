//
// Created by aminjon on 11/5/22.
//
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

auto solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    for (auto &a : A) cin >> a;

    pll a{0, 0}, b{0, 0};
    ll q;
    cin >> q;
    for (ll _ = 0; _ < q; ++_) {
        char t;
        cin >> t;

        if (t == '1') a.second += A[a.first++];
        else if (t == '2') b.second += A[b.first++];
        else if (t == '3') cout << b.second - a.second << '\n';
    }
}

int main() {
    solve();
}