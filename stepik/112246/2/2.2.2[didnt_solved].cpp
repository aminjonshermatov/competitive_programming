//
// Created by aminjon on 9/5/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t N = 2002;

auto solve() {
    int n, k; cin >> n >> k;

    vector<vector<pair<int, int>>> G(N, vector<pair<int, int>>());

    for (int i = 1; i <= k; ++i) {
        int r; cin >> r;
        for (int j = 0; j < r; ++j) {
            int pp, qq; cin >> pp >> qq;
            --pp, --qq;

            G[pp].emplace_back(qq, i);
            G[qq].emplace_back(pp, i);
        }
    }

    vector<int> dist(N, -1);
    dist[0] = 0;
    deque<pair<int, int>> q;
    q.emplace_back(0, 0);

    while (!q.empty()) {
        auto [from, from_t] = q.front(); q.pop_front();


    }

    cout << (dist[n - 1] == -1 ? -1 : dist[n - 1]) << '\n';
}

auto main() -> int32_t {
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);

    solve();
}