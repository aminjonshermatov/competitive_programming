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
    int n, k; cin >> n >> k;

    vector<int> dp(n, 0);
    dp[0] = 1;
    for (int i = 1; i < n; ++i) for (int j = k; j > 0; --j) dp[i] += i - j >= 0 ? dp[i - j] : 0;
    cout << dp[n - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    //cin >> t;
    while (t--) solve();
}