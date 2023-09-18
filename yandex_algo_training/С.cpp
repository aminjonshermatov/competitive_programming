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

void solve() {
    int n; cin >> n;
    vector<int> A(n), B(n);
    for (int i = 0; i < n; ++i) cin >> A[i] >> B[i];

    vector<int> dp0(n + 1), dp1(n + 1);
    dp0[0] = 0; dp1[0] = 0;
    for (int i = 0; i < n; ++i) {
        if ((dp0[i] + A[i] == dp1[i] + B[i]) && i + 1 < n) {
            if (A[i + 1] > B[i + 1]) {
                dp0[i + 1] = dp0[i] + A[i];
                dp1[i + 1] = dp1[i];
            } else {
                dp0[i + 1] = dp0[i];
                dp1[i + 1] = dp1[i] + B[i];
            }
        } else if (dp0[i] + A[i] < dp1[i] + B[i]) {
            dp0[i + 1] = dp0[i] + A[i];
            dp1[i + 1] = dp1[i];
        } else {
            dp0[i + 1] = dp0[i];
            dp1[i + 1] = dp1[i] + B[i];
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << ((dp0[i] - A[i - 1] == dp0[i - 1]) ? 1 : 2) << " \n"[i == n];
    }
}

//#define MEASURE_TIME

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef MEASURE_TIME
    auto start = chrono::steady_clock::now();
#endif

    int t = 1;
    //cin >> t;
    while (t--) solve();

#ifdef MEASURE_TIME
    auto finish = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
    cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";
#endif
}