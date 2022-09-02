//
// Created by aminjon on 9/1/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t N = 51u;
set<int> G[N];
int used[N], p[N], c_st = -1, c_end = -1;

auto dfs(int from) -> bool {
    used[from] = 1;

    for (auto to : G[from]) {
        if (used[to] == 0) {
            p[to] = from;
            if (dfs(to)) return true;
        } else if (used[to] == 1) {
            p[to] = from;
            c_st = to;
            c_end = from;
            return true;
        }
    }

    used[from] = 2;
    return false;
}

auto main() -> int32_t {
    int n; cin >> n;

    memset(used, 0, sizeof(int) * n);
    memset(p, -1, sizeof(int) * n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int temp; cin >> temp;
            if (temp != 0) G[i].insert(j);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (used[i] == 0 && dfs(i)) break;
    }

    if (c_st == -1) cout << 0;
    else {
        cout << 1 << '\n';

        if (false) {
            vector<int> res;
            for (int v = c_end; v != c_st; v = p[v]) res.push_back(v + 1);
            res.push_back(c_st + 1);
            reverse(res.begin(), res.end());
            cout << res.size() << '\n';
            for (auto it: res) cout << it << ' ';
            cout << '\n';
        }
    }
}