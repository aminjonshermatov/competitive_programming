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

    vector<int> dp(n, 1);
    vector<int> prv(n);
    iota(prv.begin(), prv.end(), 0);

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (A[i] < A[j]) {
                if (dp[j] < dp[i] + 1) {
                    dp[j] = dp[i] + 1;
                    prv[j] = i;
                    if (dp[j] > dp[ans]) ans = j;
                }
            }
        }
    }

    vector<int> hist;
    while (prv[ans] != ans) {
        hist.emplace_back(ans);
        ans = prv[ans];
    }
    hist.emplace_back(ans);
    reverse(hist.begin(), hist.end());
    for (auto x : hist) cout << A[x] << ' ';
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