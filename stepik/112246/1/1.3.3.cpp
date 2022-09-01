//
// Created by aminjon on 9/1/22.
//
#include "bits/stdc++.h"

using namespace std;

auto main() -> int32_t {
    int n; cin >> n;

    int e = 0, o = 0;
    for (int i = 0; i < n; ++i) {
        int cnt = 0;
        for (int j = 0; j < n; ++j) {
            int temp; cin >> temp;
            if (i == j && temp == 1) ++temp;
            cnt += temp;
        }
        if (cnt & 1) ++o;
        else ++e;
    }

    cout << e << ' ' << o << '\n';
}