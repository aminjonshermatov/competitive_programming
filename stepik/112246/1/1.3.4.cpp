//
// Created by aminjon on 9/1/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t N = 101u;
int G[N][N];

auto main() -> int32_t {
    int n; cin >> n;

    int e = 0, o = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> G[i][j];
        }
    }

    int istok = 0;
    for (int i = 0; i < n; ++i) {
        bool any_one = false;
        for (int j = 0; j < n && !any_one; ++j) {
            any_one = G[i][j] == 1;
        }
        if (!any_one) ++istok;
    }
    int stock = 0;
    for (int j = 0; j < n; ++j) {
        bool any_one = false;
        for (int i = 0; i < n && !any_one; ++i) {
            any_one = G[i][j] == 1;
        }
        if (!any_one) ++stock;
    }

    cout << stock << ' ' << istok << '\n';
}