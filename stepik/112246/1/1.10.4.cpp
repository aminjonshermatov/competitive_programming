//
// Created by aminjon on 9/3/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t N = 1e5;
vector<int> G[N];

auto main() -> int32_t {
    int n; cin >> n;

    for (int i = 1; i < n; ++i) {
        int temp; cin >> temp;
        G[--temp].emplace_back(i);
    }

    size_t ans = 0u;
    queue<int> q;
    q.push(0);

    while (!q.empty()) {
        int sz = (int)q.size();
        ans += q.size() % 2;

        while (sz-- > 0) {
            auto v = q.front(); q.pop();
            for (auto u : G[v]) q.push(u);
        }
    }

    cout << ans;
}