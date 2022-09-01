//
// Created by aminjon on 9/1/22.
//
#include "bits/stdc++.h"

using namespace std;

auto main() -> int32_t {
    int n; cin >> n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int temp; cin >> temp;
            cout << (i != j ? temp ^= 1 : 0) << ' ';
        }
        cout << '\n';
    }
}