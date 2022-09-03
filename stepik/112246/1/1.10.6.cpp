//
// Created by aminjon on 9/3/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t N = 1e2;
vector<int> G[N];
int color[N], used[N];

bool dfs(int v) {
    used[v] = 1;

    for (auto u : G[v]) {
        if (!used[u]) {
            color[u] = color[v] == 1 ? 2 : 1;
            if (dfs(u)) return true;
        } else {
            if (color[v] == color[u]) return true;
        }
    }
    return false;
}

auto main() -> int32_t {
    int n, m; cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int p, q; cin >> p >> q;

        --p, --q;
        G[p].push_back(q);
        G[q].push_back(p);
    }

    memset(color, -1, sizeof(int) * n);
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            color[i] = 1;
            if (dfs(i)) {
                cout << "NO\n";
                return 0;
            }
        }
    }
    cout << "YES\n";
    for (int i = 0; i < n; ++i) if (color[i] == 1) cout << i + 1 << ' ';
    cout << '\n';

}