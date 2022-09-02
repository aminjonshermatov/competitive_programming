//
// Created by aminjon on 9/2/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t N = 1e5 + 1;
set<int> G[N];
int used[N], D[N];

int dfs(int v) {
    used[v] = 1;

    int d = 1;
    for (auto to : G[v]) {
        if (used[to] == 0) d = max(d, dfs(to) + 1);
    }

    return D[v] = d;
}

auto main() -> int32_t {
    int n; cin >> n;

    memset(used, 0, sizeof(int) * n);
    memset(D, 0, sizeof(int) * n);

    for (int i = 1; i < n; ++i) {
        int temp; cin >> temp;
        G[--temp].insert(i);
    }

    dfs(0);
    for (int i = 0; i < n; ++i) cout << D[i] << ' ';
    cout << '\n';
}