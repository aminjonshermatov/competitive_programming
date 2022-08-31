#include "bits/stdc++.h"

using namespace std;

const int MAX_N = 2e5 + 1;
vector<int> G[MAX_N];
vector<int> W, T;

auto main() -> int32_t {
    int n, m; cin >> n >> m;

    W.assign(n + 1, 0);
    T.resize(n);

    for (int i = 0; i < m; ++i) {
        int p, q; cin >> p >> q;
        ++W[p];
        G[q].emplace_back(p);
    }

    for (auto &it : T) cin >> it;
    bool ok = true;
    for (int i = n - 1; i >= 0 && ok; --i) {
        ok = W[T[i]] <= 0;
        for (auto it : G[T[i]]) --W[it];
    }

    cout << (ok ? "YES" : "NO") << '\n';
}