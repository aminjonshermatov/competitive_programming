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

inline constexpr array<int, 2> di{-1,-2};
inline constexpr array<int, 2> dj{-2,-1};
constexpr auto k = di.size();
void solve() {
    int n, m; cin >> n >> m;
    auto ok = [&](int i, int j) -> bool { return clamp(i, 0, n - 1) == i && clamp(j, 0, m - 1) == j; };
    vector<vector<int>> dp(n, vector<int>(m, 0));
    dp[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int nk = 0; nk < k; ++nk) {
                auto ni = di[nk] + i;
                auto nj = dj[nk] + j;
                if (ok(ni, nj)) dp[i][j] += dp[ni][nj];
            }
        }
    }
    cout << dp[n - 1][m - 1] << '\n';
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