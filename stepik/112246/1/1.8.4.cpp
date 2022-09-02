//
// Created by aminjon on 9/2/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t N = 1e5 + 1;
set<int> G[N];
int used[N];
vector<int> path, ans;

int dfs(int v) {
    used[v] = 1;
    path.push_back(v);

    for (auto to : G[v]) {
        if (used[to] == 0) dfs(to);
    }

    if (path.size() > ans.size()) ans = path;
    path.pop_back();
}

auto main() -> int32_t {
    int n; cin >> n;

    memset(used, 0, sizeof(int) * n);

    for (int i = 1; i < n; ++i) {
        int temp; cin >> temp;
        G[--temp].insert(i);
        G[i].insert(temp);
    }

    dfs(0);
    memset(used, 0, sizeof(int) * n);
    dfs(ans.back());

    cout << ans.size() - 1 << '\n';
}