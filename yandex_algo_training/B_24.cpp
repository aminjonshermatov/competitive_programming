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
    array<vector<int>, 3> cost{};
    for (int i = 0; i < 3; ++i) cost[i].resize(n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < 3; ++j) cin >> cost[j][i];
    for (int i = 0; i < 3; ++i) reverse(cost[i].begin(), cost[i].end());
    array<vector<int>, 3> dp{};
    for (int i = 0; i < 3; ++i) dp[i].assign(n + 1, -1);
    dp[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i > j) {
                auto mn = inf;
                for (int k = 0; k < 3; ++k) if (dp[k][i - j - 1] != -1) mn = min(mn, dp[k][i - j - 1]);
                dp[j][i] = cost[j][i - 1] + mn;
            }
        }
    }
    int ans = inf;
    for (int i = 0; i < 3; ++i) if (dp[i][n] != -1) ans = min(ans, dp[i][n]);
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}