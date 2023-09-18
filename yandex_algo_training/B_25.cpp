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

    if (n <= 3) {
        cout << accumulate(A.begin(), A.end(), 0) << '\n';
        return;
    }

    vector<int> diff(n - 1);
    sort(A.begin(), A.end());
    for (int i = 1; i < n; ++i) diff[i - 1] = A[i] - A[i - 1];
    //for (auto x : diff) cout << x << ' ';
    //cout << '\n';

    array<vector<int>, 2> dp{};
    for (int i = 0; i < 2; ++i) dp[i].assign(n - 1, inf);
    dp[0][0] = dp[1][0] = diff[0];
    for (int i = 1; i < n - 1; ++i) {
        dp[0][i] = dp[1][i - 1];
        dp[1][i] = diff[i] + min(dp[0][i - 1], dp[1][i - 1]);
        //cout << dp[0][i] << ' ' << dp[1][i] << '\n';
    }
    cout << dp[1][n - 2] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}