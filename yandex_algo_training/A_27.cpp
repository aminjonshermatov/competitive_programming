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
    string s, t; cin >> s >> t;
    if (s.empty()) {
        cout << t.size() << '\n';
        return;
    }
    if (t.empty()) {
        cout << s.size() << '\n';
        return;
    }

    const int n(s.size());
    const int m(t.size());
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i < n; ++i) dp[i][0] = i;
    for (int j = 0; j < m; ++j) dp[0][j] = j;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dp[i][j] = min(dp[i - 1][j - 1] + (s[i - 1] != t[j - 1]), min(dp[i - 1][j], dp[i][j - 1]) + 1);
        }
    }
    cout << dp[n][m] << '\n';
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