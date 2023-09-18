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

const int MAX_N = 1e6 + 1;
array<int, MAX_N> dp{};
array<int, MAX_N> prv{};

void solve() {
    int n; cin >> n;
    vector<int> ans;
    while (prv[n] != -1) {
        ans.push_back(n);
        n = prv[n];
    }
    ans.push_back(1);
    reverse(ans.begin(), ans.end());
    cout << ans.size() - 1 << '\n';
    for (auto x : ans) cout << x << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    fill(dp.begin(), dp.end(), inf);
    fill(prv.begin(), prv.end(), -1);
    dp[1] = 0;

    queue<int> q;
    q.emplace(1);

    auto check = [&](int xx, int x) -> bool { return xx <= MAX_N && dp[xx] > dp[x] + 1; };

    while (!q.empty()) {
        auto x = q.front(); q.pop();
        auto nxt = x * 2;
        if (check(nxt, x)) {
            dp[nxt] = dp[x] + 1;
            prv[nxt] = x;
            q.emplace(nxt);
        }
        nxt = x * 3;
        if (check(nxt, x)) {
            dp[nxt] = dp[x] + 1;
            prv[nxt] = x;
            q.emplace(nxt);
        }
        nxt = x + 1;
        if (check(nxt, x)) {
            dp[nxt] = dp[x] + 1;
            prv[nxt] = x;
            q.emplace(nxt);
        }
    }

    int t = 1;
    //cin >> t;
    while (t--) solve();
}