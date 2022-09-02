//
// Created by aminjon on 9/2/22.
//
#include "bits/stdc++.h"

using namespace std;

auto main() -> int32_t {
    int n, m; cin >> n >> m;

    vector<int> W(n, 0);
    for (int i = 0; i < m; ++i) {
        int p, q; cin >> p >> q;
        ++W[--p], ++W[--q];
    }

    for (auto w : W) cout << w << ' ';
    cout << '\n';
}