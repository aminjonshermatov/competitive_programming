//
// Created by aminjon on 8/31/22.
//
#include "bits/stdc++.h"

using namespace std;

const int MAX_N = 501;
vector<char> cl;
vector<int> tp;
vector<int> G[MAX_N];

bool dfs(int v) {
    cl[v] = '1';

    for (auto to : G[v]) {
        if (cl[to] == '0' && dfs(to) || cl[to] == '1') return true;
    }
    cl[v] = '2';
    tp.emplace_back(v);
    return false;
}

auto main() -> int32_t {
    int n, m; cin >> n >> m;

    cl.assign(n + 1, '0');
    for (int i = 0; i < m; ++i) {
        int p, q; cin >> p >> q;

        G[p].emplace_back(q);
    }

    for (int i = 1; i <= n; ++i) {
        if (cl[i] == '0' && dfs(i)) goto cycle;
    }

    cout << "YES\n";
    reverse(tp.begin(), tp.end());
    for (auto it : tp) cout << it << ' ';
    cout << '\n';
    return 0;
    cycle:
    cout << "NO\n";
}