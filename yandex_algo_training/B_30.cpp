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
    vector<int> A(n);
    for (auto &a : A) cin >> a;
    int m; cin >> m;
    vector<int> B(m);
    for (auto &b : B) cin >> b;

    vector<vector<pii>> prv(n + 1, vector<pii>(m + 1, pii(-1, -1)));
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                prv[i][j] = pii(i - 1, j - 1);
            } else {
                if (dp[i - 1][j] >= dp[i][j - 1]) {
                    dp[i][j] = dp[i - 1][j];
                    prv[i][j] = pii(i - 1, j);
                } else {
                    dp[i][j] = dp[i][j - 1];
                    prv[i][j] = pii(i, j - 1);
                }
            }
        }
    }

    pii cur(n, m);
    vector<int> ans;
    while (!(cur.first == 0 && cur.second == 0)) {
        if (cur.first == -1 || cur.second == -1) break;
        if (prv[cur.first][cur.second] == pii(cur.first - 1, cur.second - 1)) {
            ans.emplace_back(A[cur.first - 1]);
            --cur.first;
            --cur.second;
        } else {
            if (prv[cur.first][cur.second] == pii(cur.first - 1, cur.second)) --cur.first;
            else --cur.second;
        }
    }
    reverse(ans.begin(), ans.end());
    for (auto x : ans) cout << x << ' ';
    cout << '\n';
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