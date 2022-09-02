//
// Created by aminjon on 9/2/22.
//
#include "bits/stdc++.h"

using namespace std;

auto main() -> int32_t {
    int n; cin >> n;

    vector<vector<int>> G(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cin >> G[i][j];
    }

    cin.ignore(1);

    vector<int> C(n);
    for (auto &c : C) cin >> c;

    int bad = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > i && G[i][j] == 1) {
                bad += (int)(C[i] != C[j]);
            }
        }
    }

    cout << bad << '\n';
}