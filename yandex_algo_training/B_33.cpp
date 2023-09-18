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
        g[v].emplace_back(u);
        g[u].emplace_back(v);
    }

    vector<int> color(n, 0);
    bool bad = false;
    auto dfs = [&](auto f, int v, int c) -> void {
        color[v] = c;
        for (auto u : g[v]) {
            if (color[u] == 0) f(f, u, -c);
            else if (color[u] != -c) {
                bad |= true;
                return;
            }
        }
    };
    for (int v = 0; v < n; ++v) if (color[v] == 0) dfs(dfs, v, 1);

    cout << (bad ? "NO" : "YES") << '\n';
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
