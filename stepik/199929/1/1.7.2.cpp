//
// Created by aminjon on 11/5/22.
//
#include <bits/stdc++.h>

using namespace std;

using ull = unsigned long long;

auto solve() {
    ull N, mx1 = 0, mx2 = 0;
    cin >> N;
    for (ull i = 0; i < N; ++i) {
        ull x;
        cin >> x;

        if (x > mx1) mx2 = mx1, mx1 = x;
        else if (x > mx2) mx2 = x;
    }

    cout << mx2 << ' ' << mx1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}