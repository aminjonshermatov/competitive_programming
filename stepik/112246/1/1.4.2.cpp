//
// Created by aminjon on 9/1/22.
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

    unordered_set<int> uniq;
    for (auto it : W) uniq.insert(it);
    cout << uniq.size();
}