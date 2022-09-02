//
// Created by aminjon on 9/2/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t N = 1e5 + 1;
set<int> G[N];
int used[N], F[N];

int dfs(int v) {
    used[v] = 1;

    int cnt = 1;
    for (auto to : G[v]) {
        if (used[to] == 0) cnt += dfs(to);
    }

    return F[v] = cnt;
}

auto main() -> int32_t {
    int n; cin >> n;

    memset(used, 0, sizeof(int) * n);
    memset(F, 0, sizeof(int) * n);

    for (int i = 1; i < n; ++i) {
        int temp; cin >> temp;
        G[--temp].insert(i);
    }

    dfs(0);
    for (int i = 0; i < n; ++i) cout << F[i] << ' ';
    cout << '\n';
}