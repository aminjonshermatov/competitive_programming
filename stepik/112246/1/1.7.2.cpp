//
// Created by aminjon on 9/1/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t N = 101u;
set<int> G[N];
int used[N], P[N], c_st = -1, c_end = -1;

auto dfs(int from) -> bool {
    used[from] = 1;

    for (auto to : G[from]) {
        if (used[to] == 0) {
            P[to] = from;
            if (dfs(to)) return true;
        } else if (used[to] == 1 && P[from] != to) {
            P[to] = from;
            c_st = to;
            c_end = from;
            return true;
        }
    }

    used[from] = 2;
    return false;
}

auto main() -> int32_t {
    int n, m; cin >> n >> m;

    memset(used, 0, sizeof(int) * n);
    memset(P, -1, sizeof(int) * n);
    for (int i = 0; i < m; ++i) {
        int p, q; cin >> p >> q;
        --p, --q;
        G[p].insert(q);
        G[q].insert(p);
    }

    bool ok = !dfs(0);
    for (int i = 0; i < n && ok; ++i) {
        ok = used[i] != 0;
    }

    if (n - 1 == m && ok) cout << "YES\n";
    else {
        cout << "NO\n";

        if (false) {
            vector<int> res;
            for (int v = c_end; v != c_st; v = P[v]) res.push_back(v + 1);
            res.push_back(c_st + 1);
            reverse(res.begin(), res.end());
            cout << res.size() << '\n';
            for (auto it: res) cout << it << ' ';
            cout << '\n';
        }
    }
}