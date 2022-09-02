//
// Created by aminjon on 9/2/22.
//
#include "bits/stdc++.h"

using namespace std;

int n, m;
vector<string> G;
array<int, 5> dk = {1,0,-1,0,1};

void dfs(int i, int j) {
    G[i][j] = '.';

    for (int k = 0; k < 4; ++k) {
        auto ii = i + dk[k];
        auto jj = j + dk[k + 1];

        if (ii >= 0 && ii < n && j >= 0 && j < m && G[ii][jj] == '#') dfs(ii, jj);
    }
}

auto main() -> int32_t {
    cin >> n >> m;

    G.resize(n);
    for (auto &l : G) cin >> l;

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (G[i][j] == '#') dfs(i, j), ++ans;
        }
    }

    cout << ans << '\n';
}