//
// Created by aminjon on 9/2/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t N = 1e5 + 1;
set<int> G[N];
int used[N];

void dfs(int v) {
    used[v] = 1;

    for (auto to : G[v]) {
        if (used[to] == 0) dfs(to);
    }
}

auto main() -> int32_t {
    int n; cin >> n;

    memset(used, 0, sizeof(int) * n);

    for (int i = 1; i < n; ++i) {
        int temp; cin >> temp;
        G[--temp].insert(i);
    }

    //dfs(0);
    vector<int> res;

    for (int i = 1; i < n; ++i) {
        if (G[i].empty()) res.emplace_back(i + 1);
    }

    for (auto v : res) cout << v << ' ';
    cout << '\n';
}