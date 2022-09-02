//
// Created by aminjon on 9/2/22.
//
#include "bits/stdc++.h"

using namespace std;

const size_t N = 1e5 + 1;
vector<int> G[N];
int used[N];

auto main() -> int32_t {
    int n, m; cin >> n >> m;
    memset(used, 0, sizeof(int) * n);

    for (int i = 0; i < m; ++i) {
        int p, q; cin >> p >> q;
        --p, --q;
        G[p].push_back(q);
        G[q].push_back(p);
    }

    stack<int> st;
    st.push(0);
    used[0] = 1;

    size_t ans = 1;
    while (!st.empty()) {
        auto v = st.top(); st.pop();

        for (auto u : G[v]) {
            if (used[u] == 0) {
                used[v] = 1;
                st.push(u);
            }
        }
        ans = max(ans, st.size());
    }

    cout << ans;
}