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
    vector<vector<int>> A(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> A[i][j];
        }
    }
    vector<vector<int>> dp(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            dp[i][j] = A[i][j] + max(i > 0 ? dp[i - 1][j] : 0, j > 0 ? dp[i][j - 1] : 0);
        }
    }

    vector<char> hist;
    pii cur(n - 1, m - 1);
    while (!(cur.first == 0 && cur.second == 0)) {
        if (cur.first > 0 && dp[cur.first][cur.second] == dp[cur.first - 1][cur.second] + A[cur.first][cur.second]) {
            hist.push_back('D');
            --cur.first;
        } else if (cur.second > 0 && dp[cur.first][cur.second] == dp[cur.first][cur.second - 1] + A[cur.first][cur.second]) {
            hist.push_back('R');
            --cur.second;
        } else assert(false);
    }
    reverse(hist.begin(), hist.end());
    cout << dp[n - 1][m - 1] << '\n';
    for (auto ch : hist) cout << ch << ' ';
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