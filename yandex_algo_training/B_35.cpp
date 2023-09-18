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
    int n; cin >> n;
    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> adj[i][j];
        }
    }

    vector<int> used(n, 0);
    vector<int> prv(n, -1);

    int start = -1, end = -1;
    auto dfs = [&](auto f, int v, int p) -> bool {
        used[v] = 1;
        for (int u = 0; u < n; ++u) if (u != p && adj[v][u]) {
            if (used[u] == 0) {
                prv[u] = v;
                if (f(f, u, v)) return true;
            } else if (used[u] == 1) {
                end = v;
                start = u;
                return true;
            }
        }
        used[v] = 2;
        return false;

    };

    for (int v = 0; v < n; ++v) if (used[v] == 0) {
        if (dfs(dfs, v, -1)) {
            cout << "YES\n";

            vector<int> cycle;
            for (int u = end; u != start; u = prv[u]) cycle.push_back(u);
            cycle.push_back(start);
            reverse(cycle.begin(), cycle.end());
            cout << cycle.size() << '\n';
            for (auto u : cycle) cout << u + 1 << ' ';
            cout << '\n';
            return;
        }
    }

    cout << "NO\n";
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
