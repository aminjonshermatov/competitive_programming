//
// Created by aminjon on 9/1/22.
//
#include "bits/stdc++.h"

using namespace std;

auto main() -> int32_t {
    int n; cin >> n;

    vector<pair<int, int>> E;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int temp; cin >> temp;
            if (j > i && temp == 1) E.emplace_back(i + 1, j + 1);
        }
    }

    for (auto &e : E) cout << e.first << ' ' << e.second << '\n';
}