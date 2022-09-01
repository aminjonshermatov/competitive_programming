//
// Created by aminjon on 9/1/22.
//
#include "bits/stdc++.h"

using namespace std;

auto main() -> int32_t {
    int n, m; cin >> n >> m;

    vector<int> W(n, 0);
    vector<pair<int, int>> E(m);
    for (int i = 0; i < m; ++i) {
        cin >> E[i].first >> E[i].second;
        ++W[--E[i].first]; ++W[--E[i].second];
    }

    int k; cin >> k; --k;
    for (auto it : W) cout << it << ' ';
    cout << '\n';
    cout << W[E[k].first] + W[E[k].second] - 2 << '\n';
}