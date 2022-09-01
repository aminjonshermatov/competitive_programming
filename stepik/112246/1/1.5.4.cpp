//
// Created by aminjon on 9/1/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t N = 1e5 + 3;
int C[N], n, m;

auto dfs(int v, int c) -> void {
    C[v] = c;

    auto next_m = m * (v / m + 1);
    for (int i = next_m - v; i <= n; i += m, next_m += m)
        if (i > 0 && C[i] > c) dfs(i, c);
}

auto main() -> int32_t {
    cin >> n >> m;

    if (m <= 1) {
        cout << n;
        return 0;
    }
    fill(C, C + n + 1, N + 10);

    int c = 0;
    for (int i = 1; i <= n; ++i) {
        if (C[i] > c) dfs(i, c++);
    }

    cout << c << '\n';
}