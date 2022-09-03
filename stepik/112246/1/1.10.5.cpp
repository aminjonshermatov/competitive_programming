//
// Created by aminjon on 9/3/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t N = 5e3;
vector<int> G[N];
int used[N];

bool dfs(int v) {
    used[v] = 1;

    for (auto u : G[v]) {
        if (used[u] == 1 || (used[u] == 0 && dfs(u))) return true;
    }

    used[v] = 2;
    return false;
}

auto main() -> int32_t {
    int n; cin >> n;

    for (int i = 0; i + 1 < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            char ch; cin >> ch;
            if (ch == 'R') G[i].emplace_back(j);
            else G[j].emplace_back(i);
        }
    }

//    for (int i = 0; i < n; ++i) {
//        for (auto j : G[i]) cout << i << ' ' << j << '\n';
//    }

    memset(used, 0, sizeof(int) * n);
    for (int i = 0; i < n; ++i) {
        if (!used[i] && dfs(i)) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
}