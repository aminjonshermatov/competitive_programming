//
// Created by aminjon on 9/1/22.
//
#include "bits/stdc++.h"

using namespace std;

auto main() -> int32_t {
    int n; cin >> n;

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int temp; cin >> temp;
            if (i == j) ans += temp;
        }
    }

    cout << ans << '\n';
}