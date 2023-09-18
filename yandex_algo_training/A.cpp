#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

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
    vector<pair<string, i64>> A;
    map<string, i64> cnt{};
    for (int _ = 0; _ < n; ++_) {
        string cmd; cin >> cmd;
        if (cmd == "add") {
            int c; string a;
            cin >> c >> a;
            A.emplace_back(a, c);
            cnt[a] += c;
        } else if (cmd == "delete") {
            i64 c; cin >> c;
            for (int i = A.size() - 1; i >= 0 && c > 0; --i) {
                auto mn = min(A[i].second, c);
                cnt[A[i].first] -= mn;
                if ((A[i].second -= mn) == 0) A.pop_back();
                c -= mn;
            }
        } else if (cmd == "get") {
            string a; cin >> a;
            cout << cnt[a] << '\n';
        }
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