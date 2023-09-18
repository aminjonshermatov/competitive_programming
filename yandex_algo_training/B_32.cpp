#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = ::int64_t;
using ld = long double;

inline constexpr auto  inf = numeric_limits<int>::max();
inline constexpr auto ninf = numeric_limits<int>::min();

using pii = pair<int, int>;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v, --u, --v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    vector<int> used(n, false);
    vector<vector<int>> comb;
    auto dfs = [&](auto f, int v) -> void {
        used[v] = true;
        comb.back().emplace_back(v);
        for (auto u : g[v]) if (!used[u]) f(f, u);
    };

    for (int v = 0; v < n; ++v) if (!used[v]) comb.emplace_back(), dfs(dfs, v);
    cout << comb.size() << '\n';
    for (auto &c : comb) {
        cout << c.size() << '\n';
        for (auto v : c) cout << v + 1 << ' ';
        cout << '\n';
    }
}

//#define TIME

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef TIME
    auto start = chrono::steady_clock::now();
#endif

    int t = 1;
    //cin >> t;
    while (t--) solve();

#ifdef TIME
    auto finish = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";
#endif
}
