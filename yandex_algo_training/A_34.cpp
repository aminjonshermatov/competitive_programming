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

inline constexpr array<int, 5> dk{1, 0, -1, 0, 1};
using pii = pair<int, int>;

void solve() {
    int n, m; cin >> n >> m;

    auto ok = [&](int i, int j) { return clamp(i, 0, n - 1) == i && clamp(j, 0, m - 1) == j; };
    using v_t = tuple<int, int, int>;
    vector<vector<int>> adj(n, vector<int>(m));
    vector<v_t> vs;
    vs.reserve(n * m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> adj[i][j];
            vs.emplace_back(adj[i][j], i, j);
        }
    }

    sort(vs.begin(), vs.end());
    vector<vector<bool>> used(n, vector<bool>(m, false));
    auto dfs = [&](auto f, int i, int j) -> void {
        used[i][j] = true;
        for (int k = 0; k < 4; ++k) {
            auto ni = i + dk[k];
            auto nj = j + dk[k + 1];
            if (!ok(ni, nj) || used[ni][nj] || adj[i][j] > adj[ni][nj]) continue;
            f(f, ni, nj);
        }
    };

    int ans = 0;
    for (auto [_, i, j] : vs) if (!used[i][j]) ++ans, dfs(dfs, i, j);
    cout << ans << '\n';
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
