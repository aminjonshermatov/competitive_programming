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

inline int to_s(int h, int m, int s) { return h * 60 * 60 + m * 60 + s; }
void print_s(int s) {
    cout << s / 3600 << ' ';
    s %= 3600;
    cout << s / 60 << ' ';
    s %= 60;
    cout << s << '\n';
}

void solve() {
    int n; cin >> n;
    vector<pii> TT;
    TT.reserve(n);
    for (int i = 0; i < n; ++i) {
        int h, m, s, t;
        char _;
        cin >> h >> _ >> m >> _ >> s >> t;
        TT.emplace_back(to_s(h, m, s), t);
    }
    if (TT.empty() || TT.back().first != to_s(18, 0, 0)) TT.emplace_back(to_s(18, 0, 0), 0);
    vector<int> T(to_s(18, 0, 0) + 1, -1);
    for (int i = 0; i < n; ++i) {
        for (int j = TT[i].first; j < TT[i + 1].first; ++j) {
            T[j] = TT[i].second;
        }
    }

    vector<int> dp(to_s(18, 0, 0) + 1, 0);
    for (int i = to_s(9, 0, 0); i < to_s(18, 0, 1); ++i) {
        dp[i] = max(dp[i - 1], dp[i]);
        if (!~T[i]) continue;
        if (clamp(i, to_s(13, 0, 0), to_s(13, 59, 59)) == i) continue ;
        if (i < to_s(13, 0, 0) && i + T[i] <= to_s(13, 0, 0)) dp[i + T[i]] = max(dp[i] + 1, dp[i + T[i]]);
        if (i > to_s(13, 59, 59) && i + T[i] <= to_s(18, 0, 0)) dp[i + T[i]] = max(dp[i] + 1, dp[i + T[i]]);
    }
    int x = to_s(13, 59, 59);
    //print_s(x);
    //cout << dp[x] << '\n';
    //cout << dp[to_s(14, 0, 0)] << ' ' << T[to_s(14, 0, 0)] << '\n';
    //cout << dp[to_s(14, 15, 0)] << ' ' << T[to_s(14, 15, 0)] << '\n';
    //cout << dp[to_s(14, 15, 1)] << ' ' << T[to_s(14, 15, 1)] << '\n';
    for (; dp[x + 1] == dp[x]; ++x) { }
    //cout << dp[to_s(13, 0, 0)] << '\n';
    //cout << dp[to_s(13, 59, 59)] << '\n';
    //cout << dp[to_s(14, 0, 0)] << '\n';
    //cout << dp[to_s(18, 0, 0)] << '\n';
    //print_s(x);
    //cout << dp[x] << '\n';
    //print_s(x + 1);
    //cout << dp[x + 1] << '\n';
    cout << dp[to_s(13, 0, 0)] + dp[to_s(18, 0, 0)] - dp[x] << '\n';
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